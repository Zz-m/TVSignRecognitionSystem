package Test;
import org.junit.After;
import org.junit.Before;
import org.junit.Test;
import com.mongodb.BasicDBObject;
import com.mongodb.DB;
import com.mongodb.DBCollection;
import com.mongodb.DBCursor;
import com.mongodb.DBObject;
import com.mongodb.Mongo;
public class MongoDBTest {
	private Mongo mg;
	private DB db;
	private DBCollection users;
	
	@Before
	public void init()throws Exception{
		try {
			mg=new Mongo("localhost",27017);
		} catch (Exception e) {
			e.printStackTrace();
		}
		db=mg.getDB("adjim");
		users=db.getCollection("speedTest");
	}
	@After
	public void destory(){
		if(mg!=null){
			mg.close();
		}
		db=null;
		users=null;
	}
	
	
	public void print(Object o){
		System.out.println(o);
	}
	
	
	public void queryAll(){
		print("查询collection中所有的数据");
		DBCursor cur=users.find();
		while(cur.hasNext()){
			print(cur.next());
		}
	}
	
	@Test
	public void add(){
		DBObject user=new BasicDBObject();
		user.put("name", "带劲萨芬");
		user.put("age", 88);
		user.put("sex", "男");
		print(users.save(user).getN());
		queryAll();
		
	}
}