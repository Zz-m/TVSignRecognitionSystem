package TvSignRecongnition;
import com.mongodb.DB;
import com.mongodb.DBCollection;
import com.mongodb.DBCursor;
import com.mongodb.DBObject;
import com.mongodb.Mongo;

/**
 * MongoDB工具类
 * @author adj
 *String host, int port, String DB, String collection
 */
public class DBUtil {
	private Mongo mg;
	private DB db;
	private DBCollection coll;
	private  String hostIp ;
	private  int port ;
	private  String dataBase ;
	private  String collection ;
	
	
	public DBUtil(String host, int port, String DB, String collection){
		this.hostIp = host;
		this.port = port;
		this.dataBase = DB;
		this.collection = collection;
	}
	
	public void init()throws Exception{
		try {
			mg=new Mongo(hostIp,port);
		} catch (Exception e) {
			e.printStackTrace();
			System.out.println("数据库连接错误，检查IP以及port");
		}
		db=mg.getDB(dataBase);
		coll=db.getCollection(collection);
	}
	
	public void destory(){
		if(mg!=null){
			mg.close();
		}
		db=null;
		coll=null;
	}
	
	
	public void print(Object o){
		System.out.println(o);
	}
	/**
	 * 查询collection全部数据并打印
	 */
	public void queryAll(){
		//print("查询users表所有的数据");
		
		DBCursor cur=coll.find();
		while(cur.hasNext()){
			print(cur.next());
		}
	}
	
	
	/**
	 * 往collection添加一条数据
	 * 
	 */
	public void add(DBObject o){
		DBObject object = o;
		//object.put("device", "ATV123");
		//object.put("电视台", "忒库电视台");
		coll.save(object);
		
		
	}
}