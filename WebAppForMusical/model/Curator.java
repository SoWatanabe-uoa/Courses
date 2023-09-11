package model;

import java.sql.ResultSet;
import java.sql.SQLException;

public class  Curator {
  private String curator_id;
  private String password;
  private DBAccess dbAccess;

  public Curator(String curator_id, String password, DBAccess dbAccess) {
    this.curator_id = curator_id;
    this.password = password;
    this.dbAccess = dbAccess;
  }

  //If curator_id is registered to DB and password corresponds to it, return true.
  //Else, return false.
  public boolean checkCurator() {
    String[] cols = new String[] {"CURATOR_ID", "PASSWORD"};
    boolean status = false;
    try {
      ResultSet rs =
          dbAccess.rowsSearch("CURATOR", cols, "CURATOR_ID='" + curator_id + "' AND PASSWORD='" + password + "'");

      if (rs.next()) {
    	  status = true;
      }
      return status;
    } catch (SQLException ex) {
      ex.printStackTrace();
      return false;
    }
  }

  public String getId() {
	    return curator_id;
	  }
}
