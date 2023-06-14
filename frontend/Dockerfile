FROM node:18
WORKDIR /ksentinel
COPY ./ ./
RUN yarn install
RUN yarn build
EXPOSE 4173
CMD yarn preview --host