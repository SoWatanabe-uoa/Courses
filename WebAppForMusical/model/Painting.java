package model;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

public class Painting {
	private int painting_id;
	private String imageURL;
	private String title;
	private String explanation;
	private List<Integer> painting_ids;
	private List<String> imageURLs;
	private DBAccess dbAccess;

	//For saveWdBalloon()
	public Painting(int painting_id, String title, String explanation, DBAccess dbAccess) {
		this.painting_id = painting_id;
		this.title = title;
		this.explanation = explanation;
		this.dbAccess = dbAccess;
	}

	//for addPainting()
	public Painting(int painting_id, String imageURL,DBAccess dbAccess) {
		this.painting_id = painting_id;
		this.imageURL = imageURL;
		this.dbAccess = dbAccess;
	}

	//for searchPainting()
	public Painting(int painting_id,DBAccess dbAccess) {
		this.painting_id = painting_id;
		this.dbAccess = dbAccess;
	}

	//for searchAllPainting() and deleteAllPaintingConfig()
	public Painting(DBAccess dbAccess) {
		this.dbAccess = dbAccess;
	}

	public boolean addPaintingId() {
		String[] cols = new String[] {"PAINTING_ID","IMAGE_URL"};
		String[] vals = new String[] {"'" + painting_id +"'","'" + imageURL +"'"};
		try {
			dbAccess.singleRowInsert("PAINTING", cols, vals);
			return true;
		} catch (SQLException ex) {
			ex.printStackTrace();
			return false;
		}
	}

	public boolean savePainting() {
		String[] cols = new String[] {"TITLE","EXPLANATION"};
		String[] vals = new String[] {"'" + title + "'","'" + explanation + "'"};
		try {
			dbAccess.singleRowUpdate("PAINTING", cols, vals, "PAINTING_ID='" + Integer.toString(painting_id) + "'");
			return true;
		} catch (SQLException ex) {
			ex.printStackTrace();
			return false;
		}
	}

	public boolean searchPainting() {
		String[] cols = new String[] {"IMAGE_URL","TITLE","EXPLANATION"};
		boolean status = false;
		try {
			ResultSet rs =
					dbAccess.rowsSearch("PAINTING", cols,
						"PAINTING_ID='" + Integer.toString(painting_id) + "'");
			while (rs.next()) {
				imageURL = rs.getString("IMAGE_URL");
				title = rs.getString("TITLE");
				explanation = rs.getString("EXPLANATION");
				status = true;
			}
			return status;
		}	catch(SQLException ex) {
			ex.printStackTrace();
			return false;
		}
	}

	public boolean searchAllPainting() {
		String[] cols = new String[] {"PAINTING_ID","IMAGE_URL"};
		boolean status = false;
		try {
			ResultSet rs =
					dbAccess.rowsSearch("PAINTING", cols,"1=1");
			painting_ids = new ArrayList<Integer>();
			imageURLs = new ArrayList<String>();
			while (rs.next()) {
				painting_ids.add(rs.getInt("PAINTING_ID"));
				imageURLs.add(rs.getString("IMAGE_URL"));
				status = true;
			}
			return status;
		}	catch(SQLException ex) {
			ex.printStackTrace();
			return false;
		}
	}

	public boolean deleteAllPaintingConfig() {
		try {
			dbAccess.rowsDelete("Painting", "1=1");
			return true;
		} catch (SQLException ex) {
			ex.printStackTrace();
			return false;
		}
	}

	public int getPaintingId(){
		return painting_id;
	}

	public String getImageURL(){
		return imageURL;
	}

	public String getTitle(){
		return title;
	}

	public String getExplanation(){
		return explanation;
	}

	public List<Integer> getPaintingIds(){
		return painting_ids;
	}

	public List<String> getAllPaintingURL(){
		return imageURLs;
	}
}
