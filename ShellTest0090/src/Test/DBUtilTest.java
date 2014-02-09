package Test;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;

import TvSignRecongnition.DBUtil;

import com.mongodb.BasicDBObject;
import com.mongodb.DBObject;


public class DBUtilTest {
	DBUtil util = null;

	
	private  String hostIp = "127.0.0.1";
	private  int port = 27017;
	private  String dataBase = "DBUtilTest";
	private  String collection = "Sunday";
	
	
	@Before
	public void Initialization(){
		util = new DBUtil(hostIp, port, dataBase, collection);
		try {
			util.init();
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	
	}
	
	@After
	public void destroy(){
		util.destory();
	}
	
	
	
	public void print(Object o){
		System.out.println(o);
	}
	
	@Test
	public void TestqueryAll(){
		util.queryAll();
	}
	
	
	@Test
	public void Testadd(){
		DBObject user=new BasicDBObject();
		user.put("name", "´ø¾¢Èø·Ò");
		user.put("age", 88);
		user.put("sex", "ÄÐ");
		util.add(user);	
	}
}

