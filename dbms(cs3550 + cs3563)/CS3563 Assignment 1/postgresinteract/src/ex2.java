
import java.sql.*;
import java.util.Scanner;

public class ex2 {
	
	public static void main(String[] args) {
		
		try
		{
			
	
			System.out.println("Enter the subject code whose prereq you want to find");
			Connection conn = DriverManager.getConnection("jdbc:postgresql://localhost:5432/univdb","postgres","123");
			Statement stmt = conn.createStatement();			
			Scanner sc= new Scanner(System.in);
			String inputid = sc.next();
			

			
			String sql = "with recursive c_prereq AS( SELECT prereq_id FROM prereq WHERE course_id = '" + inputid
                    + "' UNION ALL"
                    + " SELECT cp.prereq_id "
                    + "FROM c_prereq "
                    + "JOIN "
                    + "prereq cp "
                    + "ON "
                    + "c_prereq.prereq_id = cp.course_id ) "
                    + "cycle prereq_id set is_cycle"
                    + " using path select course.title, c_prereq.prereq_id from c_prereq,course"
                    + " where not "
                    + "is_cycle and course.course_id = c_prereq.prereq_id ;";
			
			ResultSet rset = stmt.executeQuery(sql);
			
			while(rset.next()) {
				for(int i=1 ;i<=2 ;i++) {
			System.out.print(rset.getString(i))  ;System.out.print("  ");}System.out.println();
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
