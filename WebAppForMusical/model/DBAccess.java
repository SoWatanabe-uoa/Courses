package model;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

public class DBAccess {
  Connection conn;

  public DBAccess() throws ClassNotFoundException, SQLException {
	//Constants for DB connection
    String DATABASE_NAME = "dialogue_creator";
    String PROPATIES = "?characterEncoding=UTF-8&serverTimezone=JST";
    String URL = "jdbc:mySQL://localhost/" + DATABASE_NAME+PROPATIES;
    //User constant for D
    String USER = "ie04";
    String PASS = "Watching_4";
  //Connect to MySQL
    Class.forName("com.mysql.cj.jdbc.Driver");
    conn = DriverManager.getConnection(URL, USER, PASS);
  }

  public ResultSet rowsSearch(String tableName, String[] columnNameArray, String condition)
      throws SQLException {
    Statement st = conn.createStatement();
    String sqls = "SELECT " + columnNameArray[0];
    for (int i = 1; i < columnNameArray.length; i++) {
      sqls = sqls + "," + columnNameArray[i];
    }
    sqls = sqls + " FROM " + tableName + " WHERE " + condition;
    //System.out.println(sqls);
    return st.executeQuery(sqls);
  }

  public boolean singleRowInsert(String tableName, String[] columnNameArray,
      String[] columnValuesArray) throws SQLException {
    Statement st = conn.createStatement();
    String sqls = "INSERT INTO " + tableName + "(" + columnNameArray[0];
    for (int i = 1; i < columnNameArray.length; i++) {
      sqls = sqls + "," + columnNameArray[i];
    }
    sqls = sqls + ") VALUES(" + columnValuesArray[0];
    for (int i = 1; i < columnValuesArray.length; i++) {
      sqls = sqls + "," + columnValuesArray[i];
    }
    sqls = sqls + ")";
    //System.out.println(sqls);
    st.executeUpdate(sqls);
    return true;
  }

  public boolean singleRowUpdate(String tableName, String[] columnNameArray, String[] columnValuesArray,
	      String condition) throws SQLException {
	    Statement st = conn.createStatement();
	    String sqls = "UPDATE " + tableName + " SET " + columnNameArray[0] + "=" + columnValuesArray[0];
	    for (int i = 1; i < columnNameArray.length; i++) {
	      sqls = sqls + "," + columnNameArray[i] + "=" + columnValuesArray[i];
	    }
	    sqls = sqls + " WHERE " + condition;
	    //System.out.println(sqls);
	    st.executeUpdate(sqls);
	    return true;
	  }

  public boolean rowsDelete(String tableName, String condition)
	      throws SQLException {
	    Statement st = conn.createStatement();
	    String sqls = "DELETE FROM " + tableName + " WHERE " + condition;
	    //System.out.println(sqls);
	    st.executeUpdate(sqls);
	    return true;
	  }
}
