package TvSignRecongnition;
import java.io.BufferedReader;
import java.io.InputStreamReader;

import com.mongodb.BasicDBObject;
import com.mongodb.DBObject;


/**
 * 执行对制定目录的匹配并输出结果存入数据库
 * @author adj
 *
 */
public class Excution {
	public static void excuteCommand(String[] args) {
		String commands;
		try {
			commands = CommandBuilder.buildCommand(args);
			if(commands.equals("fail")){		
				return;
			}
			Process process = Runtime.getRuntime().exec(commands);

			// for showing the info on screen

			InputStreamReader ir = new InputStreamReader(
					process.getInputStream());
			BufferedReader input = new BufferedReader(ir);
			String line;
			//String device;
			//String tvSign;
			DBUtil util = new DBUtil("192.168.2.75", 27017, "TvSign", "result");
			try {
				util.init();
			} catch (Exception e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
				System.out.println("连接数据库失败");
			}
			while ((line = input.readLine()) != null) {
				System.out.println(line);
				System.out.println("");
				String[] result = Analysis.analyse(line);
				System.out.println("设备名："+result[0]+"     "+"电视台："+result[1]);
				DBObject result1=new BasicDBObject();
				result1.put(result[0], result[1]);
				util.add(result1);
				System.out.println("");
				System.out.println("");
				System.out.println("");
			}
			util.destory();
			if(input != null){
				input.close();
			}
			if(ir != null){
				ir.close();
			}
			if(process != null){
				process.destroy();
			}			

		}// end try

		catch (java.io.IOException e) {

			System.err.println("IOException " + e.getMessage());

		}
	}
}
