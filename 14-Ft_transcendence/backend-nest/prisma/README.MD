# Run these commands inside the backend container at startup

Enter the container (if you are running in local, skip this first step)

```
docker exec -it backend /bin/bash
```


Create new migration files and apply them.

```
cd prisma;
make clean;
make migrate-dev;
```

Launch prisma studio for easy debugging

```
npx prisma studio
```

