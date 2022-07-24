-- Keep a log of any SQL queries you execute as you solve the mystery.
/*list of suspects here:
| Vanessa   | 5P2BI95       | (725) 555-4692 | 2963008352    |X
| Karen     | IH61GO8       | (841) 555-3728 | 5031682798    |X
| Barry     | 6P58WS2       | (301) 555-4174 | 7526138472    |X
| Christine | XE95071       | (608) 555-9302 |               |X
| Alexander | 8P9NEU9       | (801) 555-9266 |               |X
| Noah      | 11J91FW       | (959) 555-4871 | 1095374669    |X
| Iman      | L93JTIZ       | (829) 555-5269 | 7049073643       |V
| Sofia     | G412CB7       | (130) 555-0289 | 1695452385    |XV
| Luca      | 4328GD8       | (389) 555-5198 | 8496433585       |VV
| Diana     | 322W7JE       | (770) 555-1861 | 3592750733       |V
| Kathleen  | PF37ZVK       | (960) 555-2044 | 2628207874    |X
| Kelsey    | 0NTHK55       | (499) 555-9472 | 8294398571    |XV
| Bruce     | 94KL13X       | (367) 555-5533 | 5773159633       |VV
| Alice     | 1M92998       | (031) 555-9915 | 1679711307    |X

Escape within 10 minutes of the robery
Legget Street atm
*/
select description from crime_scene_reports where month = 7 and day = 28 and street = "Humphrey Street";
select transcript from interviews where year = "2021" and month = "7" and day = "28";
select license_plate from bakery_security_logs where activity = "exit" and year = "2021" and month = "07" and hour = "10" and minute >= "15" and minute <= "25";
/*liste des voitures qui sont parties entre 10h15 et 10h25
5P2BI95       |
| 94KL13X       |
| 6P58WS2       |
| 4328GD8       |
| G412CB7       |
| L93JTIZ       |
| 322W7JE       |
| 0NTHK55       |
| 11J91FW       |
| PF37ZVK       |
| 1M92998       |
| XE95071       |
| IH61GO8       |
| 8P9NEU9        */

select distinct people.name,people.license_plate,people.phone_number,people.passport_number from people, bakery_security_logs where people.license_plate in (select license_plate from bakery_security_logs where activity = "exit" and year = "2021" and month = "07" and hour = "10" and minute >= "15" and minute <= "25");
/*Liste des personnes qui sont parties de la boulangerie entre 10h15 et 10h25
| Vanessa   | 5P2BI95       | (725) 555-4692 | 2963008352      |
| Karen     | IH61GO8       | (841) 555-3728 | 5031682798      |
| Barry     | 6P58WS2       | (301) 555-4174 | 7526138472      |
| Christine | XE95071       | (608) 555-9302 |                 |
| Alexander | 8P9NEU9       | (801) 555-9266 |                 |
| Noah      | 11J91FW       | (959) 555-4871 | 1095374669      |
| Iman      | L93JTIZ       | (829) 555-5269 | 7049073643      |
| Sofia     | G412CB7       | (130) 555-0289 | 1695452385      |
| Luca      | 4328GD8       | (389) 555-5198 | 8496433585      |
| Diana     | 322W7JE       | (770) 555-1861 | 3592750733      |
| Kathleen  | PF37ZVK       | (960) 555-2044 | 2628207874      |
| Kelsey    | 0NTHK55       | (499) 555-9472 | 8294398571      |
| Bruce     | 94KL13X       | (367) 555-5533 | 5773159633      |
| Alice     | 1M92998       | (031) 555-9915 | 1679711307      |*/

select account_number,atm_location from atm_transactions where year = "2021" and month = "07" and day = "28" and atm_location = "Leggett Street";
/* | account_number |  atm_location  |
+----------------+----------------+
| 28500762       | Leggett Street |
| 28296815       | Leggett Street |
| 76054385       | Leggett Street |
| 49610011       | Leggett Street |
| 16153065       | Leggett Street |
| 86363979       | Leggett Street |
| 25506511       | Leggett Street |
| 81061156       | Leggett Street |
| 26013199       | Leggett Street |*/

select distinct people.name,people.phone_number,people.passport_number,bank_accounts.account_number from people,bank_accounts,atm_transactions where people.id = bank_accounts.person_id and bank_accounts.account_number = atm_transactions.account_number and atm_transactions.account_number in (select account_number from atm_transactions where year = "2021" and month = "07" and day = "28" and atm_location = "Leggett Street");
/*|  name   |  phone_number  | passport_number | account_number |
+---------+----------------+-----------------+----------------+
| Bruce   | (367) 555-5533 | 5773159633      | 49610011       |
| Kaelyn  | (098) 555-1164 | 8304650265      | 86363979       |
| Diana   | (770) 555-1861 | 3592750733      | 26013199       |
| Brooke  | (122) 555-4581 | 4408372428      | 16153065       |
| Kenny   | (826) 555-1652 | 9878712108      | 28296815       |
| Iman    | (829) 555-5269 | 7049073643      | 25506511       |
| Luca    | (389) 555-5198 | 8496433585      | 28500762       |
| Taylor  | (286) 555-6063 | 1988161715      | 76054385       |
| Benista | (338) 555-6650 | 9586786673      | 81061156       |*/

select flights.id,flights.destination_airport_id,airports.city,flights.hour,flights.minute from flights,airports where airports.id = flights.destination_airport_id and year = "2021" and month = "7" and day = "29" order by hour;
/*| id | destination_airport_id |     city      | hour | minute |
+----+------------------------+---------------+------+--------+
| 36 | 4                      | New York City | 8    | 20     |
| 43 | 1                      | Chicago       | 9    | 30     |
| 23 | 11                     | San Francisco | 12   | 15     |
| 53 | 9                      | Tokyo         | 15   | 20     |
| 18 | 6                      | Boston        | 16   | 0      |*/

select distinct people.name,people.passport_number from passengers,flights,people where passengers.flight_id = flights.id and passengers.passport_number = people.passport_number and flights.id = "36" and flights.year = "2021" and flights.month = "07" and flights.day = "29";
/*|  name  | passport_number |
+--------+-----------------+
| Doris  | 7214083635      |
| Sofia  | 1695452385      |
| Bruce  | 5773159633      |
| Edward | 1540955065      |
| Kelsey | 8294398571      |
| Taylor | 1988161715      |
| Kenny  | 9878712108      |
| Luca   | 8496433585      |*/

select people.name from people,phone_calls where people.phone_number = phone_calls.caller and phone_calls.year = "2021" and phone_calls.month = "07" and phone_calls.day = "28" intersect select distinct people.name from passengers,flights,people where passengers.flight_id = flights.id and passengers.passport_number = people.passport_number and flights.id = "36" and flights.year = "2021" and flights.month = "07" and flights.day = "29";
select people.name,phone_calls.duration from people,phone_calls where people.phone_number = phone_calls.receiver and people.name = "Bruce" and phone_calls.year = "2021" and phone_calls.month = "07" and phone_calls.day = "28";
/*I think it's Bruce*/
select people.name,phone_calls.duration from people,phone_calls where people.phone_number = phone_calls.receiver and phone_calls.caller = "(367) 555-5533" and phone_calls.year = "2021" and phone_calls.month = "07" and phone_calls.day = "28";

