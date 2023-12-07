# 42RomaLuiss__ft_transcendence
Final 42 project 
Create a website with real-time multiplayer online game and online chat

Links to team resources :  
- [Notes, scope, documentation](https://docs.google.com/document/d/1iVzydO9ddOBO0K5R5PnRqfjk7vo0vF1s-J6WsYeJJWE/edit?usp=sharing)
- [Notion](https://www.notion.so/42-ft-transcendence/4644276802fa46fcbba8f6be900c2972?v=cba097541aaf4a14abe5997047a5a352&pvs=4)
# ft_transcendence

Run on docker:
``` docker-compose up --build ```

For let it running in local:
change file .env POSTGRES_HOST


``` docker-compose up --build -d ```
``` docker stop backend```
``` cd backend-nest```
``` npm install``` (only the first time)
``` npm run start:dev``` (running for development, the server will look for changes in the code and restart automatically)
``` npm run start:prod``` (running for production)

How to Run Prisma

Ensure you installed the prisma CLI and prisma client</br>
(on the cluster machines, install them locally for we do not have global permissions)

````
npm i -D prisma
npm i -g @prisma/client

-g = global installation
-D = local installation
````

Each Time you make a change to the `.schema` file, run

```
npx prisma generate

npx prisma migrate dev (only if you are working locally)
```

Create a `.env` file in your prisma directory

with this environment variable if local execution
```
DATABASE_URL="postgresql://dbuser:dbpwd@localhost:5433/database?schema=public&connect_timeout=19000"
```

with this environment variable if containerized execution
```
DATABASE_URL="postgresql://dbuser:dbpwd@database:5432/database?schema=public&connect_timeout=19000"
```