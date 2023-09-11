package model;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

public class WordBalloon {
	private int painting_id;
	private int size;
	private String pre_description;
	private int top;
	private int left;
	private boolean flipped;
	private List<Integer> sizes;
	private List<String> pre_descriptions;
	private List<Integer> tops;
	private List<Integer> lefts;
	private List<Boolean> flippeds;
	private DBAccess dbAccess;

	public WordBalloon(int painting_id, int size, String pre_description, int top, int left, boolean flipped, DBAccess dbAccess) {
		this.painting_id = painting_id;
		this.size = size;
		this.pre_description = pre_description;
		this.top = top;
		this.left = left;
		this.flipped = flipped;
		this.dbAccess = dbAccess;
	}

	public WordBalloon(int painting_id, DBAccess dbAccess) {
		this.painting_id = painting_id;
		this.dbAccess = dbAccess;
	}

	public WordBalloon(DBAccess dbAccess) {
		this.dbAccess = dbAccess;
	}

	public boolean saveWdBalloon() {
		String[] cols = new String[] {"PAINTING_ID","SIZE","PRE_DESCRIPTION","_TOP","_LEFT","FLIPPED"};
		String[] vals = new String[] {"'" + Integer.toString(painting_id) + "'",
                                      "'" + Integer.toString(size) + "'",
                                      "'" + pre_description + "'",
                                      "'" + Integer.toString(top) + "'",
                                      "'" + Integer.toString(left) + "'",
                                            Boolean.toString(flipped)};
		try {
			dbAccess.singleRowInsert("WORDBALLOON", cols, vals);
			return true;
		} catch (SQLException ex) {
			ex.printStackTrace();
			return false;
		}
	}

	public boolean searchWdBalloon() {
		String[] cols = new String[] {"PAINTING_ID","SIZE","PRE_DESCRIPTION","_TOP","_LEFT","FLIPPED"};
		boolean status = false;
		try {
			ResultSet rs =
					dbAccess.rowsSearch("WORDBALLOON", cols,
						"PAINTING_ID='" + Integer.toString(painting_id) + "'");
			pre_descriptions = new ArrayList<String>();
			sizes = new ArrayList<Integer>();
			tops = new ArrayList<Integer>();
			lefts = new ArrayList<Integer>();
			flippeds = new ArrayList<Boolean>();
			while (rs.next()) {
				pre_descriptions.add(rs.getString("PRE_DESCRIPTION"));
				sizes.add(rs.getInt("SIZE"));
				tops.add(rs.getInt("_TOP"));
				lefts.add(rs.getInt("_LEFT"));
				flippeds.add(rs.getBoolean("FLIPPED"));
				status = true;
			}
			return status;
		}	catch(SQLException ex) {
			ex.printStackTrace();
			return false;
		}
	}

	public boolean deleteAllWdBalloonConfig() {
		try {
			dbAccess.rowsDelete("WORDBALLOON", "1=1");
			return true;
		} catch (SQLException ex) {
			ex.printStackTrace();
			return false;
		}
	}

	public List<Integer> getSizes(){
		return sizes;
	}

	public List<String> getPre_descriptions(){
		return pre_descriptions;
	}

	public List<Integer> getTops(){
		return tops;
	}

	public List<Integer> getLefts(){
		return lefts;
	}

	public List<Boolean> getFlippeds(){
		return flippeds;
	}
}
