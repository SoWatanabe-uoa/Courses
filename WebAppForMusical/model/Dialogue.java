package model;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

public class Dialogue {
	private int painting_id;
	private String ImageURL;
	private List<String> selectedDialogueImageURLs;
	private DBAccess dbAccess;

	//In case of using saveDialogue()
	public Dialogue(int painting_id, String ImageURL, DBAccess dbAccess) {
		this.painting_id = painting_id;
		this.ImageURL = ImageURL;
		this.dbAccess = dbAccess;
	}

	//In case of using searchDialogue()
	public Dialogue(int painting_id, DBAccess dbAccess) {
		this.painting_id = painting_id;
		this.dbAccess = dbAccess;
	}

	//Add one row which contains 2 values into DIALOGUE table.
	public boolean saveDialogue() {
		String[] cols = new String[] {"PAINTING_ID", "IMAGE_URL"};
		String[] vals = new String[] {"'" + Integer.toString(painting_id) + "'",
				"'" + ImageURL + "'"};
	    try {
	      dbAccess.singleRowInsert("DIALOGUE", cols, vals);
	      return true;
	    } catch (SQLException ex) {
	      ex.printStackTrace();
	      return false;
	    }
	}

	//Extract all rows whose value of PAINTING_ID equals to painting_id
	public boolean searchDialogue() {
		String[] cols = new String[] {"PAINTING_ID", "IMAGE_URL"};
	    boolean status = false;
	    try {
	      ResultSet rs =
	          dbAccess.rowsSearch("DIALOGUE", cols, "PAINTING_ID='" + Integer.toString(painting_id) + "'");

	      selectedDialogueImageURLs = new ArrayList<String>();
	      while (rs.next()) {
	        selectedDialogueImageURLs.add(rs.getString("IMAGE_URL"));
	        status = true;
	      }
	      return status;
	    } catch (SQLException ex) {
	      ex.printStackTrace();
	      return false;
	    }
	}

	public List<String> getSelectedDialogueImageURLs(){
		return selectedDialogueImageURLs;
	}

}
