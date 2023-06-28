FROM nginx:latest
WORKDIR /usr/share/nginx
COPY ./build/html ./html
EXPOSE 80
CMD ["nginx","-g","daemon off;"]