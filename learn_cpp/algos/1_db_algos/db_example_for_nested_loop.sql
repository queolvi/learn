USE db_nl;

CREATE TABLE table_1 (
    num INT PRIMARY KEY,
    str VARCHAR(255)
);

CREATE TABLE table_2 LIKE table_1;
CREATE TABLE table_3 LIKE table_1;
CREATE TABLE table_4 LIKE table_1;
CREATE TABLE table_5 LIKE table_1;
INSERT INTO table_1 (num, str) VALUES 
(0, 'ab'), (1, 'cd');

INSERT INTO table_2 (num, str) VALUES 
(2, 'ef'), (3, 'gh');

INSERT INTO table_3 (num, str) VALUES 
(4, 'ij'), (5, 'kl');

INSERT INTO table_4 (num, str) VALUES 
(6, 'mn'), (7, 'op');

INSERT INTO table_5 (num, str) VALUES 
(8, 'qr'), (9, 'st');
SELECT * FROM table_1;
