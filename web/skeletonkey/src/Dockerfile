FROM node:16-alpine

EXPOSE 8000

WORKDIR /app
COPY package.json package-lock.json ./
RUN npm ci

COPY static ./static
COPY index.js ./

CMD npm start
