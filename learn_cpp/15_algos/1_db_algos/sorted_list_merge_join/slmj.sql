CREATE DATABASE IF NOT EXISTS slmj;
USE slmj;

CREATE TABLE IF NOT EXISTS first (
    val INT PRIMARY KEY,
    t TEXT
);

CREATE TABLE IF NOT EXISTS second (
    val INT PRIMARY KEY,
    t TEXT
);

INSERT IGNORE INTO first (val, t) VALUES
    (1, 'Alice'),
    (2, 'Bob'),
    (3, 'Charlie'),
    (5, 'Eve');

INSERT IGNORE INTO second (val, t) VALUES
    (1, 'HR'),
    (2, 'Engineering'), 
    (3, 'Marketing'),
    (4, 'Sales'),
    (5, 'Finance');
