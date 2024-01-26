CREATE TABLE new_students (
    id INTEGER,
    student_name TEXT NOT NULL,
    house_id integer NOT NULL,
    PRIMARY KEY (id),
    FOREIGN KEY (house_id) REFERENCES houses(id)
);

CREATE TABLE houses (
    id INTEGER,
    house_name TEXT NOT NULL,
    head_id INTEGER NOT NULL,
    PRIMARY KEY (id),
    FOREIGN KEY (head_id) REFERENCES heads(id)
);

CREATE TABLE heads (
    id INTEGER,
    head_name TEXT NOT NULL,
    PRIMARY KEY (id)
);
