.mode csv
.import ./CSV/teams.csv teams --skip 1
UPDATE teams
SET team = UPPER(TRIM(team));
.import ./CSV/players.csv players --skip 1
UPDATE players
SET ilkid = UPPER(TRIM(ilkid));
.import ./CSV/player_playoffs.csv player_playoffs --skip 1
UPDATE player_playoffs
SET ilkid = UPPER(TRIM(ilkid));
.import ./CSV/player_playoffs_career.csv player_playoffs_career --skip 1
UPDATE player_playoffs_career
SET ilkid = UPPER(TRIM(ilkid));
.import ./CSV/coaches_career.csv coaches_career --skip 1
UPDATE coaches_career
SET coachid = UPPER(TRIM(coachid));
.import ./CSV/coaches_season.csv coaches_season --skip 1
UPDATE coaches_season
SET coachid = UPPER(TRIM(coachid));
.import ./CSV/player_regular_season.csv player_regular_season --skip 1
UPDATE player_regular_season
SET ilkid = UPPER(TRIM(ilkid));
.import ./CSV/player_regular_season_career.csv player_regular_season_career --skip 1
UPDATE player_regular_season_career
SET ilkid = UPPER(TRIM(ilkid));