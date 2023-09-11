package model;

import java.sql.ResultSet;
import java.sql.SQLException;

public class CoverPage {
	private int coverpage_id;
	private String imageURL;
	private DBAccess dbAccess;

	//In case of using saveCoverPage()
	public CoverPage(String imageURL, DBAccess dbAccess) {
		this.imageURL = imageURL;
		this.dbAccess = dbAccess;
	}

	//In case of using searchAllCoverPage()
	public CoverPage(DBAccess dbAccess) {
		this.dbAccess = dbAccess;
	}

	public boolean saveCoverPage() {
		String[] cols = new String[] {"IMAGE_URL"};
		String[] vals = new String[] {"'" + imageURL + "'"};
	    try {
	      dbAccess.singleRowInsert("COVERPAGE", cols, vals);
	      return true;
	    } catch (SQLException ex) {
	      ex.printStackTrace();
	      return false;
	    }
	}

	public boolean searchAllCoverPage() {
		String[] cols = new String[] {"COVERPAGE_ID", "IMAGE_URL"};
	    boolean status = false;
	    try {
	      ResultSet rs =
	          dbAccess.rowsSearch("COVERPAGE", cols, "1=1");

	      while (rs.next()) {
	    	  coverpage_id = rs.getInt("COVERPAGE_ID");
		      imageURL = rs.getString("IMAGE_URL");
		      status = true;
	      }
	      return status;
	    } catch (SQLException ex) {
	      ex.printStackTrace();
	      return false;
	    }
	}

	public boolean deleteAllCoverPageConfig() {
		try {
			dbAccess.rowsDelete("COVERPAGE", "1=1");
			return true;
		} catch (SQLException ex) {
			ex.printStackTrace();
			return false;
		}
	}

	public int getCoverPageId(){
		return coverpage_id;
	}
	public String getImageURL(){
		return imageURL;
	}

}
