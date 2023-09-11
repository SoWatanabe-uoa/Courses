package model;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

public class LightBulb {
	private int coverpage_id;
	private int painting_id;
	private int top;
	private int left;
	private List<Integer> painting_ids;
	private List<Integer> tops;
	private List<Integer> lefts;
	private DBAccess dbAccess;

	//for saveLightBulb()
	public LightBulb(int coverpage_id, int painting_id, int top, int left, DBAccess dbAccess) {
		this.coverpage_id = coverpage_id;
		this.painting_id = painting_id;
		this.top = top;
		this.left = left;
		this.dbAccess = dbAccess;
	}

	//for searchLightBulb()
	public LightBulb(int coverpage_id, DBAccess dbAccess) {
		this.coverpage_id = coverpage_id;
		this.dbAccess = dbAccess;
	}

	//for deleteAllLightBulbConfig()
	public LightBulb(DBAccess dbAccess) {
		this.dbAccess = dbAccess;
	}

	public boolean saveLightBulb() {
		String[] cols = new String[] {"COVERPAGE_ID","PAINTING_ID","_TOP","_LEFT"};
		String[] vals = new String[] {"'" + Integer.toString(coverpage_id) + "'",
                                      "'" + Integer.toString(painting_id) + "'",
                                      "'" + Integer.toString(top) + "'",
                                      "'" + Integer.toString(left) + "'"};
		try {
			dbAccess.singleRowInsert("LIGHT_BULB", cols, vals);
			return true;
		} catch (SQLException ex) {
			ex.printStackTrace();
			return false;
		}
	}

	public boolean searchLightBulb() {
		String[] cols = new String[] {"PAINTING_ID","_TOP","_LEFT"};
		boolean status = false;
		try {
			ResultSet rs =
					dbAccess.rowsSearch("LIGHT_BULB", cols,
						"COVERPAGE_ID='" + Integer.toString(coverpage_id) + "'");
			painting_ids = new ArrayList<Integer>();
			tops = new ArrayList<Integer>();
			lefts = new ArrayList<Integer>();
			while (rs.next()) {
				painting_ids.add(rs.getInt("PAINTING_ID"));
				tops.add(rs.getInt("_TOP"));
				lefts.add(rs.getInt("_LEFT"));
				status = true;
			}
			return status;
		}	catch(SQLException ex) {
			ex.printStackTrace();
			return false;
		}
	}

	public boolean deleteAllLightBulbConfig() {
		try {
			dbAccess.rowsDelete("LIGHT_BULB", "1=1");
			return true;
		} catch (SQLException ex) {
			ex.printStackTrace();
			return false;
		}
	}

	public List<Integer> getPaintingIds(){
		return painting_ids;
	}

	public List<Integer> getTops(){
		return tops;
	}

	public List<Integer> getLefts(){
		return lefts;
	}
}

