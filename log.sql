-- Keep a log of any SQL queries you execute as you solve the mystery.

-- 1. get descriptions of events taking place on the date and location of the theft
SELECT description FROM crime_scene_reports WHERE year = 2021 AND month = 7 AND day = 28 AND street = 'Humphrey Street';

-- | 295 | Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery. Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery. |

-- 2. get interview transcripts from the day of the theft
SELECT transcript FROM interviews WHERE year = 2021 AND day = 28 AND month = 7;

-- | 161 | Ruth    | Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away. If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.                                                          |
-- | 162 | Eugene  | I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.                                                                                                 |
-- | 163 | Raymond | As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket. |

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
-- match passport numbers in passengers to people.passport_number
-- match passengers.flight_id to flights.id
-- match airports.id to flights.destination_airport_id
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

-- 8. use remaining suspects from query 7 to get flight info
SELECT * FROM flights WHERE id = (
    SELECT flight_id FROM passengers, people WHERE passengers.passport_number = people.passport_number AND people.name IN (
        SELECT people.name FROM atm_transactions, people, bank_accounts WHERE bank_accounts.person_id = people.id AND bank_accounts.account_number = atm_transactions.account_number AND year = 2021 AND month = 7 AND day = 28 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw' AND people.name IN (
            SELECT DISTINCT(name) FROM people, phone_calls WHERE caller = phone_number AND year = 2021 AND day = 28 AND month = 7 AND duration < 60 AND license_plate IN (
                SELECT license_plate FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute > 15 AND minute < 25 AND activity = 'exit'
            )
        )
    )
);

-- 9. check that origin airport is Fiftyville, meaning the person flying could have been the thief.
SELECT DISTINCT(city) FROM airports, flights WHERE origin_airport_id = 8 AND flights.origin_airport_id = airports.id;

-- 10. match passengers on flight from query 8 to names of remaining suspects
SELECT name FROM people, passengers WHERE flight_id = 18 AND people.passport_number = passengers.passport_number AND people.name IN ('Bruce', 'Diana');

-- 11. get destination of thief.
SELECT DISTINCT(city) FROM airports, flights WHERE destination_airport_id = 6 AND flights.destination_airport_id = airports.id;

-- 12. get receiver of calls made by thief at the time of the theft.
SELECT receiver FROM phone_calls, people WHERE duration < 60 AND year = 2021 AND day = 28 AND month = 7 AND caller = people.phone_number AND people.name = 'Diana';

-- 13. get the name of receiver.
SELECT name FROM people WHERE phone_number = (SELECT receiver FROM phone_calls, people WHERE duration < 60 AND year = 2021 AND day = 28 AND month = 7 AND caller = people.phone_number AND people.name = 'Diana');