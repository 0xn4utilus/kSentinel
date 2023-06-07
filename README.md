# Development
Follow the following instructions to get started:

<hr>

## kSentinel backend
The backend is built on the microservices architecture that consists of the following four services:
- tracing
- auth
- healthcheck
- apisecurity

### API Routes (Tracing)
/api/register -> Register a new user <br>
/api/login -> Login <br>
/api/auth/create_device  -> Register a new device <br>


<hr>

## kSentinel core
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