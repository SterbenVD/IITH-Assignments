

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.Statement;
import java.util.Scanner;

public class ex5 {
	public static void main(String args[]) {
	try {
		
		
		Connection conn = DriverManager.getConnection("jdbc:postgresql://localhost:5432/univdb","postgres","123");
		Statement stmt = conn.createStatement();
		
		Scanner sc= new Scanner(System.in);
		
		
		System.out.println("Enter the value of k");
		int k = sc.nextInt();

		
		String sql1 = "CREATE OR REPLACE FUNCTION  cal_cgpa(IDI varchar(5)) \n"
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
		
		
		

		stmt.execute(sql1) ;
		 String supsql;
    
		System.out.println("Press 1 if you want overall cgpa \n Press 2 if you want department wise cgpa \n Press 3 if you want course wise cgpa");
		int inp = sc.nextInt();
		
		if(inp ==1) {
		
			supsql = "select cal_cgpa(ID) as cgpa ,ID,name from student order by cgpa desc LIMIT "+k +" ;";
			   ResultSet suprset = stmt.executeQuery(supsql);
		        while(suprset.next()) {
		        	for(int i =1 ;i<=3;i++) {
		      	  String cgpa = suprset.getString(i);System.out.print("  ");
		      	  System.out.print(cgpa);} System.out.println("");
		        }
		}
		else if(inp ==2) {
			System.out.println("Enter deprtment name") ;
			String inputid = sc.next();
			 supsql = "select cal_cgpa(ID) as cgpa,ID,name from student where dept_name = '"+inputid+"' order by cgpa desc LIMIT "+k +" ;";
			   ResultSet suprset = stmt.executeQuery(supsql);
		        while(suprset.next()) {
		        	for(int i =1 ;i<=3;i++) {
		      	  String cgpa = suprset.getString(i);System.out.print("  ");
		      	  System.out.print(cgpa);} System.out.println("");
		        }
		}
		else if(inp ==3) {
			System.out.println("Enter course name") ;
			String courseinp = sc.next();
		supsql = "select cal_cgpa(takes.ID) as cgpa ,takes.ID,student.name from student ,takes where   course_id = '"+courseinp+"' and student.ID =takes.ID order by cgpa desc LIMIT "+k +" ;";
		   ResultSet suprset = stmt.executeQuery(supsql);
	        while(suprset.next()) {
	        	for(int i =1 ;i<=3;i++) {
	      	  String cgpa = suprset.getString(i);System.out.print("  ");
	      	  System.out.print(cgpa);} System.out.println("");
	        }	
			
		}
		
     
        sc.close();
     	
  		
		
	}
	
	
	catch(Exception sqle)
	{
		System.out.println("Exception : " + sqle) ;
	}
	
}
}