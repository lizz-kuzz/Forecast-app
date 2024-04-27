-- main table for every think

create table weather(
    user_name text, 
    city int, 
    data_ DATE NOT NULL, 
    time_ time, 
    temp float, 
    temp_feels_like float, 
    pressure float, 
    wind float, 
    type_ text
);


insert into weather(
    user_name, 
    city, 
    data_, 
    time_, 
    temp, 
    temp_feels_like, 
    pressure, 
    wind, 
    type_
) values
    ('kate', 1, '2024-04-26', '3:00:00', 12.2, 12.4, 345, 5.3, 'cloudy');

delete from weather
where user_name = 'liza' and
      city = 1;

select * from weather 
where user_name = 'liza' and
      city = 1;


