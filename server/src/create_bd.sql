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


select  weather.city, 
        weather.user_name,
        weather.data_, 
        avg(temp), 
        avg(temp_feels_like), 
        avg(pressure),
        avg(wind)
from weather where weather.city = 0 and weather.user_name = 'real' 
group by weather.data_, 
        weather.city, 
        weather.user_name 
order by weather.data_;


create table city_coord(
    city integer, 
    lat float, 
    lon float
);

insert into city_coord(
    city, 
    lat, 
    lon
) values    (1, 55.751244, 37.618423),
            (2, 59.937500, 30.308600),
            (3, 55.050000, 82.950000),
            (4, 56.835600, 60.612800),
            (5, 55.939831, 37.503434);

select * from city_coord 
    where city = 1;