FROM gcc:latest
RUN apt modernize-sources && apt update && apt full-upgrade && apt autoremove
RUN apt install -y --no-install-recommends cmake ninja-build ca-certificates pip
COPY . /usr/src/EGL-cpp/
WORKDIR /usr/src/EGL-cpp/
RUN mkdir -p -m 0700 ~/.ssh && ssh-keyscan github.com >> ~/.ssh/known_hosts
RUN --mount=type=ssh cmake -S . -B build/ -G Ninja
RUN pip install --break-system-packages Jinja2
RUN cmake --build build/
# FROM debian:latest AS runtime
# RUN apt modernize-sources && apt update && apt full-upgrade && apt autoremove
# COPY --from=compilador /usr/src/EGL-cpp/ /usr/src/EGL-cpp/
# WORKDIR /usr/src/EGL-cpp/
# CMD ./build/src