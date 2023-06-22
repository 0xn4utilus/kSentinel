## Get started

Install the latest version of docker and docker-compose and run the command:
```
docker-compose up
```
It will start the frontend, services and the database containers. Visit http://127.0.0.1:4173 to view the kSentinel UI.

# Development
Follow the following instructions to get started:

<hr>

## kSentinel backend
The backend is built on the microservices architecture that consists of the following four services:
- tracing
- auth
- healthcheck
- apisecurity

### API Routes (Auth)
```
POST /api/auth/register -> Register a new user
POST /api/auth/login -> Login
```
<hr>

### API Routes (kscore)
```
POST /api/kscore/device -> Register a new device
POST /api/kscore/
```

### Environment Variables (Auth Service)
```
DB_USER = 
DB_PASSWORD = 
DB_PORT = 
DB_HOST = 
DB_NAME = 
JWT_SECRET = 
ALLOWED_ORIGINS = "http://127.0.0.1:5173, http://localhost:5173"
```
## kSentinel core
- Install libcurl using `sudo apt install libcurl4-openssl-dev`
- Clone the repository 
```
git clone https://github.com/InfoSecIITR/kSentinel
```
- Install the latest version of [cmake](https://cmake.org/)
- Change the directory to `core` and run `./build.sh`. It will install the `kSentinel` binary in `core/bin` directory.

### Directory structure
- `include` - Contains all the header files
- `lib` - Contains the libraries needed by kSentinel
- `src` - Contains the source code
- `progs` - Contains eBPF programs
- `tests` - Contains tests for automated testing

### Environment Variables
```
KS_CONFIG_DIR -> Absolute path of a directory to store logs and configuration files. It must be set by the user
```

<hr>


### Building the documentation
```py
pip install -U sphinx
pip install sphinx-rtd-theme
pip install recommonmark
```
Place this Makefile at the root of the `docs` directory and run the command `make html` to build the html files for documentation
```
# Minimal makefile for Sphinx documentation
#

# You can set these variables from the command line, and also
# from the environment for the first two.
SPHINXOPTS    ?=
SPHINXBUILD   ?= sphinx-build
SOURCEDIR     = source
BUILDDIR      = build

# Put it first so that "make" without argument is like "make help".
help:
	@$(SPHINXBUILD) -M help "$(SOURCEDIR)" "$(BUILDDIR)" $(SPHINXOPTS) $(O)

.PHONY: help Makefile

# Catch-all target: route all unknown targets to Sphinx using the new
# "make mode" option.  $(O) is meant as a shortcut for $(SPHINXOPTS).
%: Makefile
	@$(SPHINXBUILD) -M $@ "$(SOURCEDIR)" "$(BUILDDIR)" $(SPHINXOPTS) $(O)

```
