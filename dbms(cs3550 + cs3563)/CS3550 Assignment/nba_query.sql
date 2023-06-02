SELECT position,
    count()
FROM players
GROUP BY position;
--
SELECT T2.year as year,
T1.gp + T2.gp as gp
FROM (
        SELECT year,
            sum(gp) as gp
        FROM player_regular_season
        GROUP BY year
    ) AS T1
    INNER JOIN (
        SELECT year,
            sum(gp) as gp
        FROM player_playoffs
        GROUP BY year
    ) AS T2 ON T1.year = T2.year
ORDER BY gp DESC,
    year
LIMIT 5;
--
ALTER TABLE player_regular_season_career
ADD eff INT;
UPDATE player_regular_season_career
SET eff = (
        pts + reb + asts + stl + blk - ((fga - fgm) + (fta - ftm) + turnover)
    );
SELECT ilkid,
    gp,
    eff
FROM (
        SELECT ilkid,
            sum(gp) as gp,
            sum(eff) as eff
        FROM player_regular_season_career
        GROUP BY ilkid
    )
WHERE (gp >= 500)
ORDER BY eff DESC
LIMIT 10;
--
SELECT COUNT() from (
WITH comp(ilkid, year, gp) AS (
    SELECT ilkid,
        year,
        sum(gp) as gp
    FROM player_regular_season
    GROUP BY ilkid,
        year
)
SELECT ilkid
FROM player_regular_season
WHERE year = 1990
GROUP BY ilkid
EXCEPT
SELECT T1.ilkid as ilkid
FROM comp AS T1
    INNER JOIN comp AS T2 ON T1.ilkid = T2.ilkid
WHERE T1.year = 1990
    AND T1.year != T2.year
    AND T1.gp <= T2.gp
);
--
WITH comp(ilkid, gp, eff) AS (
SELECT ilkid,
    sum(gp) as gp,
    sum(eff) as eff
FROM player_regular_season_career
GROUP BY ilkid
)
SELECT ilkid
FROM player_regular_season_career
GROUP BY ilkid
EXCEPT
SELECT T1.ilkid as ilkid
FROM comp AS T1
    INNER JOIN comp AS T2
WHERE T1.eff < T2.eff
    AND T1.gp < T2.gp;