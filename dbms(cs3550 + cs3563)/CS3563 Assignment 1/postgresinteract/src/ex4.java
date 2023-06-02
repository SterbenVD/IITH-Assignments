// package univdb;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.Statement;
import java.util.*;

public class ex4 {
public static void main(String args[]) {
	
	try {
		Connection conn = DriverManager.getConnection("jdbc:postgresql://localhost:5432/univdb","postgres","123");
		Statement stmt = conn.createStatement();
		
		Scanner sc= new Scanner(System.in);
		String inputid = sc.nextLine();
		

		String sql = "DROP FUNCTION cal_cgpa(character varying);\n"
				+ "DROP TABLE lal;\n"
				+ "DROP TABLE table1 ;\n"
				+ "DROP TABLE table2 ;";
		
		String sql2 = "CREATE OR REPLACE FUNCTION  cal_cgpa(IDI varchar(5)) \n"
				+ "				RETURNS numeric(2,2) AS $$\n"
				+ "				   DECLARE \n"
				+ "				     tot_points numeric ; \n"
				+ "					 credit numeric ;\n"
				+ "					 points numeric ;\n"
				+ "			\n"
				+ "				   BEGIN\n"
				+ "				   \n"
				+ "				   CREATE TABLE lal(sub , grade,id) as (select course_id,grade,ID  from takes where ID = IDI);\n"
				+ "                   CREATE TABLE table1(sub ,grade,id,credit) as \n"
				+ "				   (select sub ,grade ,id,credits from lal ,course where lal.sub = course.course_id);\n"
				+ "				   \n"
				+ "				   CREATE TABLE table2(grades varchar(2),points integer) ;\n"
				+ "                   INSERT INTO table2 VALUES('A+', 10), ('A ', 9) ,('A-', 8) ,('B+', 7) ,('B ', 6) ,('B-', 5) ,('C+', 4) ,('C ', 3) ,('C-', 2) ;\n"
				+ "-- 				      select table1.grade ,table1.credit as credit  ,table2.grades , table2.points as points\n"
				+ "select sum(table2.points * table1.credit),sum(table1.credit) into points,credit\n"
				+ "					  from table1 INNER JOIN table2 ON table1.grade = table2.grades group by id ;\n"
				+ "-- 					  select SUM(points*credit)/SUM(credit);\n"
				+ "					   tot_points = points /credit ; \n"
				+ "			\n" 
				+ "DROP TABLE lal;\n"
				+ "DROP TABLE table1 ;\n"
				+ "DROP TABLE table2 ;"
				+ "				      RETURN tot_points ;\n"
				+ "				   END; $$  LANGUAGE plpgsql ;";
		
		
		     String sql3 = "select * from cal_cgpa('"+inputid +"')" ;
	
	//	stmt.execute(sql);
		stmt.execute(sql2);
		ResultSet rset = stmt.executeQuery(sql3) ;
		
		while(rset.next()) {
			System.out.println(rset.getString(1)) ;
			}
		
		
		stmt.close();
				conn.close();
			   sc.close();

	}
	
	
	catch(Exception sqle)
	{
		System.out.println("Exception : " + sqle) ;
	}
	
	
	
	
	
	
}
}
