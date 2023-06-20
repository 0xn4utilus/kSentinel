package controllers

import (
	"encoding/json"
	"log"
	"net/http"
	"os"
	"time"

	emailverifier "github.com/AfterShip/email-verifier"
	"github.com/InfoSecIITR/kSentinel/auth/models"
	"github.com/gin-gonic/gin"
	"github.com/gofiber/fiber/v2"
	"github.com/golang-jwt/jwt/v4"
)

type LoginResponse struct {
	Message string
	Token   string
}

type UserParser struct {
	Username string `json:"username"`
	Email    string `json:"email"`
	Password string `json:"password"`
}

type JWTClaims struct {
	Username string `json:"username"`
	jwt.RegisteredClaims
}



func Register(c *fiber.Ctx) error {
	userParser := new(UserParser)
	if err := c.BodyParser(userParser); err != nil {
		log.Println(err)
	}
	if userParser.Username == "" || userParser.Email == "" || userParser.Password == "" {
		return c.Status(http.StatusBadRequest).SendString("All fields are required")
	}
	if len(userParser.Username) > 20 || len(userParser.Email) > 255 || len(userParser.Password) > 255 {
		return c.Status(http.StatusBadRequest).SendString("Maximum length of fields exceeded")
	}

	if user, err := models.GetUserInfoByUsername(userParser.Username); err == nil {
		if user.Username != "" {
			return c.Status(http.StatusBadRequest).SendString("Username already taken")
		}
	}
	if user, err := models.GetUserInfoByEmail(userParser.Email); err == nil {
		if user.Email != "" {
			return c.Status(http.StatusBadRequest).SendString("Email already taken")
		}
	}
	if err := models.InsertNewUser(userParser.Username, userParser.Email, HashPassword(userParser.Password)); err != nil {
		return c.Status(http.StatusBadRequest).SendString("Registration failed")
	}

	return c.Status(http.StatusOK).SendString("Registration successful")
}

func Login(c *fiber.Ctx) error {
	var resp LoginResponse
	var jsonResp []byte
	var userParser UserParser
	err := json.Unmarshal(c.Body(),&userParser)
	if err!=nil{
		return c.Status(http.StatusBadRequest).SendString(err.Error())
	}
	if userParser.Username == "" || userParser.Password == "" {
		resp = LoginResponse{
			Message: "All fields are required",
			Token:   "",
		}
		jsonResp, _ = json.Marshal(resp)
		return c.Status(http.StatusBadRequest).SendString(string(jsonResp))
	}

	if len(userParser.Username) > 72 || len(userParser.Password) > 72 {
		resp = LoginResponse{
			Message: "Maximum length of fields exceeded",
			Token:   "",
		}
		jsonResp, _ = json.Marshal(resp)
		return c.Status(http.StatusBadRequest).SendString(string(jsonResp))
	}

	if userParser.Username != "" {
		userDetails, _ := models.GetUserInfoByUsername(userParser.Username)
		if userDetails.Username == "" {
			resp = LoginResponse{
				Message: "Username not found",
				Token:   "",
			}
			jsonResp, _ = json.Marshal(resp)
			return c.Status(http.StatusBadRequest).SendString(string(jsonResp))
		}
		if err := ComparePassword(userDetails.Password, userParser.Password); err == nil {
			expirationTime := time.Now().Add(7 * 24 * time.Hour)
			claims := &JWTClaims{
				Username: userDetails.Username,
				RegisteredClaims: jwt.RegisteredClaims{
					ExpiresAt: jwt.NewNumericDate(expirationTime),
				},
			}
			token := jwt.NewWithClaims(jwt.SigningMethodHS256, claims)
			// Create the JWT string
			jwtKey := []byte(os.Getenv("JWT_SECRET"))
			tokenString, err := token.SignedString(jwtKey)
			if err != nil {
				log.Println(err)
				resp = LoginResponse{
					Message: "Login failed",
					Token:   "",
				}
				jsonResp, _ = json.Marshal(resp)
				return c.Status(http.StatusInternalServerError).SendString(string(jsonResp))
			}
			// Set Cookie
			cookie := new(fiber.Cookie)
			cookie.Name = "token"
			cookie.Value = tokenString
			cookie.Expires = expirationTime

			c.Cookie(cookie)
			resp = LoginResponse{
				Message: "Login successful",
				Token:   tokenString,
			}
			jsonResp, _ = json.Marshal(resp)
			return c.Status(http.StatusOK).SendString(string(jsonResp))
		}

	}
	resp = LoginResponse{
		Message: "Login failed",
		Token:   "",
	}
	jsonResp, _ = json.Marshal(resp)
	return c.Status(http.StatusUnauthorized).SendString(string(jsonResp))
}

var (
	verifier = emailverifier.NewVerifier()
)

func verify_email() {
	verifier = verifier.EnableSMTPCheck()

	verifier = verifier.EnableDomainSuggest()
	//verifier = verifier.AddDisposableDomains([]string{"tractorjj.com"})

	router := gin.Default()
	router.LoadHTMLGlob("templates/*.html")

	//router.GET("/verifyemail", verEmailGetHandler)
	//router.POST("/verifyemail", verEmailPostHandler)
	err := router.Run("localhost:8080")
	if err != nil {
		log.Fatal(err)
	}
}

func verEmailGetHandler(c *gin.Context) {
	c.HTML(http.StatusOK, "ver-email.html", nil)
}

func verEmailPostHandler(c *gin.Context) {
	log.Println("verEmailPostHandler running")
	email := c.PostForm("email")
	ret, err := verifier.Verify(email)
	if err != nil {
		log.Println("verify email address failed, error is: ", err)
		c.HTML(http.StatusInternalServerError, "ver-email.html", gin.H{"message": "unable to register email addresss, please try again"})
		return
	}

	//log.Println("email validation result", ret)
	//log.Println("Email:", ret.Email, "\nReachable:", ret.Reachable, "\nSyntax:", ret.Syntax, "\nSMTP:", ret.SMTP, "\nGravatar:", ret.Gravatar, "\nSuggestion:", ret.Suggestion, "\nDisposable:", ret.Disposable, "\nRoleAccount:", ret.RoleAccount, "\nFree:", ret.Free, "\nHasMxRecords:", ret.HasMxRecords)

	// needs @ and . for starters
	if !ret.Syntax.Valid {
		//log.Println("email address syntax is invalid")
		c.HTML(http.StatusBadRequest, "ver-email.html", gin.H{"message": "email address syntax is invalid"})
		return
	}
	if ret.Disposable {
		//log.Println("sorry, we do not accept disposable email addresses")
		c.HTML(http.StatusBadRequest, "ver-email.html", gin.H{"message": "sorry, we do not accept disposable email addresses"})
		return
	}
	if ret.Suggestion != "" {
		//log.Println("email address is not reachable, looking for ", ret.Suggestion, "instead?")
		c.HTML(http.StatusBadRequest, "ver-email.html", gin.H{"message": "email address is not reachable, looking for " + ret.Suggestion + " instead?"})
		return
	}
	// possible return string values: yes, no, unkown
	if ret.Reachable == "no" {
		//log.Println("email address is not reachable")
		c.HTML(http.StatusBadRequest, "ver-email.html", gin.H{"message": "email address was unreachable"})
		return
	}
	// check MX records so we know DNS setup properly to recieve emails
	if !ret.HasMxRecords {
		//log.Println("domain entered not properly setup to recieve emails, MX record not found")
		c.HTML(http.StatusBadRequest, "ver-email.html", gin.H{"message": "domain entered not properly setup to recieve emails, MX record not found"})
		return
	}
	// ... code to register user
	c.HTML(http.StatusOK, "ver-email-result.html", gin.H{"email": email})
}
