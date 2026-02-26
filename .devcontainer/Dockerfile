FROM gcc:latest
RUN apt modernize-sources && apt update && apt full-upgrade -y --no-install-recommends && apt autoremove
RUN apt install -y cmake ninja-build pip gdb lldb
RUN pip install --break-system-packages Jinja2
RUN mkdir -p -m 0700 ~/.ssh && ssh-keyscan github.com >> ~/.ssh/known_hosts
RUN adduser vscode
USER vscode