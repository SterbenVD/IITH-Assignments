// package univdb;
import java.sql.*;
import java.util.* ;

public class ex1 {
	
	public static void main(String[] args) {
		
		try
		{
			Connection conn = DriverManager.getConnection("jdbc:postgresql://localhost:5432/univdb","postgres","123");
			Statement stmt = conn.createStatement();


			Scanner sc= new Scanner(System.in);
			System.out.println("Enter TAble name");
			String tablename=sc.nextLine() ;
			System.out.println("Enter number");
			int rownum = sc.nextInt();

			String sql = "select * from "+tablename+" LIMIT "+ rownum;
    		ResultSet rset  = stmt.executeQuery(sql);
    		ResultSetMetaData rsmd = rset.getMetaData();
    		int colnum = rsmd.getColumnCount();

    		
    		int []arr  ;
    		arr = new int[rsmd.getColumnCount()];
    		for(int i = 1 ;i<=colnum ;i++) {
    			String name = rsmd.getColumnName(i);
    		 arr[i-1]  = name.length();
    			System.out.print(rsmd.getColumnName(i));
    			int mmm = arr[i-1];
    			for(int k =20;k>mmm;k--) {
					System.out.print(" ");
				}
    		}
    		System.out.println();
    		int flag = 0;
    		while(rset.next()) {
    			
    			for(int i=1;i<=colnum;i++) {
    				String temp= rset.getString(i);
    				int entrylen = temp.length();
    				System.out.print(rset.getString(i)+" ");
    				int mm = arr[i-1];
    				for(int k =20;k>entrylen;k--) {
    					System.out.print(" ");
    				}
    				
    			}
    			
    			System.out.println();
    			flag++;
    			if(flag==rownum) {break;}
    		}
    		
			stmt.close();
			conn.close();
		}

			catch(Exception sqle)
			{
				System.out.println("Exception : " + sqle) ;
			}
			
		
		
	
	}

}
