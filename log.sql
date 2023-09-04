-- Keep a log of any SQL queries you execute as you solve the mystery.

-- 1. get descriptions of events taking place on the date and location of the theft
SELECT description FROM crime_scene_reports WHERE year = 2021 AND month = 7 AND day = 28 AND street = 'Humphrey Street';

-- 2. get interview transcripts from the day of the theft
SELECT transcript FROM interviews WHERE year = 2021 AND day = 28 AND month = 7;

-- 3. match license plates of cars leaving bakery around the time of the theft to people who own cars and get the names of the ppl who own those cars (i.e. suspects) and when they left.
SELECT name, minute FROM people, bakery_security_logs WHERE people.license_plate = bakery_security_logs.license_plate AND year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute > 15 AND minute < 25 AND activity = 'exit';

-- 4. of the suspects from query 3, how many of them withdrew money from the ATM on Leggett Street the day of the theft AND made a call that lasted for less than a minute?
SELECT DISTINCT(name) FROM people, atm_transactions WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw' AND name IN (
    SELECT DISTINCT(name) FROM people, phone_calls WHERE caller = phone_number AND year = 2021 AND day = 28 AND month = 7 AND duration < 60 AND license_plate IN (
        SELECT license_plate FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute > 15 AND minute < 25 AND activity = 'exit'
        )
    );

-- 5. of the remaining suspects from query 4, who has a bank account?
SELECT DISTINCT(people.name) FROM atm_transactions, people, bank_accounts WHERE bank_accounts.person_id = people.id AND bank_accounts.account_number = atm_transactions.account_number AND name IN (
    SELECT DISTINCT(name) FROM people, atm_transactions WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw' AND name IN (
        SELECT DISTINCT(name) FROM people, phone_calls WHERE caller = phone_number AND year = 2021 AND day = 28 AND month = 7 AND duration < 60 AND license_plate IN (
            SELECT license_plate FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute > 15 AND minute < 25 AND activity = 'exit'
        )
    )
);

-- 6. of the remaining suspects, who took a flight on or after the day and time of the theft and where did they go?
SELECT DISTINCT(people.name), airports.city, year, month, day, hour, minute FROM people, flights, passengers, airports WHERE people.passport_number = passengers.passport_number AND passengers.flight_id = flights.id AND airports.id = flights.destination_airport_id AND year = 2021 AND month = 7 AND day >= 28 AND name IN (
    SELECT DISTINCT(people.name) FROM atm_transactions, people, bank_accounts WHERE bank_accounts.person_id = people.id AND bank_accounts.account_number = atm_transactions.account_number AND name IN (
    SELECT DISTINCT(name) FROM people, atm_transactions WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw' AND name IN (
        SELECT DISTINCT(name) FROM people, phone_calls WHERE caller = phone_number AND year = 2021 AND day = 28 AND month = 7 AND duration < 60 AND license_plate IN (
            SELECT license_plate FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute > 15 AND minute < 25 AND activity = 'exit'
            )
        )
    )
);

-- 7. it must be Bruce b/c if Diana had stolen the duck, she wouldn't go back to Fiftyville so soon. so who did Bruce call the day of the theft?
SELECT name FROM people WHERE phone_number = (SELECT receiver FROM phone_calls, people WHERE duration < 60 AND year = 2021 AND day = 28 AND month = 7 AND caller = people.phone_number AND people.name = 'Bruce');