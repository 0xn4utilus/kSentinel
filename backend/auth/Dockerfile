FROM ubuntu:22.04
WORKDIR /ksentinelAuth
COPY ./auth ./
RUN useradd ksenchan
RUN chown -R root:ksenchan /ksentinelAuth && chmod -R 750 /ksentinelAuth
USER ksenchan
EXPOSE 8080
CMD /ksentinelAuth/auth