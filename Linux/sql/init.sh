#/bin/bash
# Нагрузочный тест

# Удалили базу
dropdb sql_test
# Создали базу
createdb -T template0 sql_test
# Многократно ее заполнили
i = 0
for ((i = 0; i < 10; i = i + 1));
do
    psql sql_test < ./tables.sql
done
