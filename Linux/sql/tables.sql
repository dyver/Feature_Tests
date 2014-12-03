drop table messages;

create table messages (
    id integer,
    text varchar(128)
);

insert into messages values (1, 'Test');

select * from messages;