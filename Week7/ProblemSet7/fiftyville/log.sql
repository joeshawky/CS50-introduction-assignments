-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Checking crime scene reports
select * from crime_scene_reports
where month = 7 AND day = 28;

--There are 3 witnesses, the theft of the duck happened at 10:15am, at the Humphrey Street bakery.
select name, transcript from interviews
where year = 2021 and month = 7 and day = 28;

--Eugene says he saw the thief withdrawing money prior to the theft from the ATM on Leggett Street
--The following query gives us the names of the persons that have done such transaction.
select name from people
where id in (
    select bank_accounts.person_id from bank_accounts
    where bank_accounts.account_number in (
        select account_number from atm_transactions
        where year = 2021
        and month = 7
        and day = 28
        and transaction_type = 'withdraw'
        and atm_location = 'Leggett Street'
    )
)
--Previous query gives us the following names:
-- (Bruce, Diana, Luca, Brooke, Taylor, Benista, Iman, Kenny)

--Raymond gives us 2 clues, first clue is that the thief calls someone for less than a minute within 10 minutes of the theft.
select caller.name as caller_name, receiver.name as receiver_name from phone_calls
join people caller on caller.phone_number = phone_calls.caller
join people receiver on receiver.phone_number = phone_calls.receiver
    where day = 28
    and month = 7
    and year = 2021
    and duration < 60

-- The query above gives us a table for callers names and receivers names, it is as follows:
/*
    Sofia   --> Jack
    Kelsey  --> Larry
    Bruce   --> Robin
    Kelsey  --> Melissa
    Taylor  --> James
    Diana   --> Philip
    Carina  --> Jacqueline
    Kenny   --> Doris
    Benista --> Anna
*/

-- Raymond's second clue is that in the call they were planning to take the earliest flight out of Fifyville tomorrow, which would be 29/7/2021
select people.name, origin.city as origin_city, destination.city as destination_city, flights.hour, flights.minute from people
join passengers on passengers.passport_number = people.passport_number
join flights on flights.id = passengers.flight_id
join airports origin on origin.id = flights.origin_airport_id
join airports destination on destination.id = flights.destination_airport_id
where origin.city = 'Fiftyville'
and flights.day = 29
and flights.month = 7
and flights.year = 2021
order by flights.hour ASC, flights.minute ASC;

-- Earliest flight on 29/7/2021 is new york city's flight, the following people went on this flight.
-- (Doris, Sofia, Bruce, Edward, Kelsey, Taylor, Kenny, Luca)

-- Ruth gave the tip that within 10 minutes of the theft, she saw the thief get into a car and leave the bakery parking lot.
select name from people
join bakery_security_logs on bakery_security_logs.license_plate = people.license_plate
and bakery_security_logs.minute >= 5
and bakery_security_logs.minute <= 25
and bakery_security_logs.hour = 10
where bakery_security_logs.day = 28
and bakery_security_logs.month = 7
and bakery_security_logs.year = 2021
and bakery_security_logs.activity = 'exit'
ORDER BY name ASC;

-- Previous query gives us a list of people who left the parking lot within 10 minutes:
-- (Barry, Bruce, Diana, Iman, Kelsey, Luca, Sofia, Vanessa)

select name from people
where name in ('Barry', 'Bruce', 'Diana', 'Iman', 'Kelsey', 'Luca', 'Sofia', 'Vanessa')
and name in ('Doris', 'Sofia', 'Bruce', 'Edward', 'Kelsey', 'Taylor', 'Kenny', 'Luca')
and name in ('Sofia', 'Kelsey', 'Bruce', 'Kelsey', 'Taylor', 'Diana', 'Carina', 'Kenny', 'Benista')
and name in ('Bruce', 'Diana', 'Luca', 'Brooke', 'Taylor', 'Benista', 'Iman', 'Kenny')

-- This gives us the thief who is Bruce, he went to new york city on 29/7/2021 at 8:20, and his accomplice is Robin
