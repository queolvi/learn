CREATE DATABASE IF NOT EXISTS hash_join_demo;
USE hash_join_demo;

CREATE TABLE IF NOT EXISTS employees (
    emp_id INT PRIMARY KEY,
    emp_name VARCHAR(50),
    dept_id INT,
    salary DECIMAL(10,2)
);
CREATE TABLE IF NOT EXISTS departments (
    dept_id INT,
    dept_name VARCHAR(50),
    location VARCHAR(50),
    budget DECIMAL(15,2)
);
INSERT INTO employees VALUES
    (1, 'Иван Петров', 101, 75000),
    (2, 'Мария Сидорова', 102, 82000),
    (3, 'Алексей Иванов', 101, 68000),
    (4, 'Елена Смирнова', 103, 91000),
    (5, 'Дмитрий Кузнецов', 102, 78000);
INSERT INTO departments VALUES
    (101, 'Разработка', 'Москва', 1000000),
    (101, 'Разработка', 'Санкт-Петербург', 800000),
    (102, 'Маркетинг', 'Москва', 500000),
    (103, 'Финансы', 'Новосибирск', 750000),
    (104, 'HR', 'Казань', 300000),
    (105, 'Продажи', 'Екатеринбург', 900000),
    (102, 'Маркетинг', 'Владивосток', 400000);
