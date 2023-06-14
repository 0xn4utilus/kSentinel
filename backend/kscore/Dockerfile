FROM ubuntu:22.04
WORKDIR /ksentinel
COPY ./kscore ./
RUN useradd ksenchan
RUN chown -R root:ksenchan /ksentinel && chmod -R 750 /ksentinel
USER ksenchan
EXPOSE 9000
CMD /ksentinel/kscore