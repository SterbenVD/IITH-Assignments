create or replace view supertable as select * from teaches inner join section using  (course_id, sec_id, semester, year);

CREATE OR REPLACE FUNCTION trigger_check()
RETURNS TRIGGER
AS $$
BEGIN 
   if exists ( 
   select * from supertable where NEW.ID = supertable.ID AND NEW.semester= supertable.semester AND NEW.year =supertable.year and supertable.time_slot_id = (
   		select time_slot_id from supertable as temp where (NEW.semester= temp.semester AND NEW.year = temp.year AND temp.course_id=NEW.course_id AND temp.sec_id=NEW.sec_id))
   
								   AND (supertable.course_id<>NEW.course_id or supertable.sec_id <> NEW.sec_id) ) then
   rollback;return NULL ;
   END IF;

return new ;
END;
$$ LANGUAGE PLPGSQL;




CREATE OR REPLACE FUNCTION trigger_check2()
RETURNS TRIGGER
AS $$
BEGIN 
	if exists ( 
   select * from supertable where NEW.time_slot_id = supertable.time_slot_id AND NEW.semester= supertable.semester AND NEW.year =supertable.year and supertable.id = (
   		select id from supertable as temp where (NEW.semester= temp.semester AND NEW.year = temp.year AND temp.course_id=NEW.course_id AND temp.sec_id=NEW.sec_id))
   
								   AND (supertable.course_id<>NEW.course_id or supertable.sec_id <> NEW.sec_id) ) then
   rollback;return NULL ;
   END IF;
   return new ;
END;
$$ LANGUAGE PLPGSQL;





   Create or REPLACE trigger check_instructor_insert_in_teaches 
   after insert OR update 
   on teaches
   for each row
   execute function trigger_check();

   Create or REPLACE trigger check_instructor_insert_in_section
   after update
   on section
   for each row
   execute function trigger_check2();
