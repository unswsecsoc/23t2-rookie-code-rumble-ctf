docker exec -it infra-teller-db-1 mysql -D challengedb -u user --password=F55wH5XesZKcsTxj -e "SELECT SUM(tokens_used) AS total, AVG(tokens_used) AS average, COUNT(tokens_used) AS requests FROM openai_usage_tracking"
docker exec -it infra-teller-db-1 mysql -D challengedb -u user --password=F55wH5XesZKcsTxj -e "SELECT username, SUM(tokens_used) AS total, AVG(tokens_used) AS average, COUNT(tokens_used) AS requests FROM openai_usage_tracking GROUP BY username ORDER BY total DESC;"
