# build stage
FROM node:20.2.0-bullseye-slim as build-stage

WORKDIR /app

COPY package*.json ./

RUN npm i vite && \
	npm i vite-plugin-node-polyfills && \
	npm install socket.io-client && \
	npm install -g http-server

RUN npm install

COPY . .

# ENTRYPOINT ["npm", "run", "dev"]
RUN npm run build

# production stage
FROM nginx:stable-alpine as production-stage
COPY nginx.conf /etc/nginx/conf.d/default.conf

COPY --from=build-stage /app/dist /usr/share/nginx/html
# EXPOSE 80
CMD ["nginx", "-g", "daemon off;"]