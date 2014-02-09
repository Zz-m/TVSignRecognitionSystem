package Test;
import java.util.regex.*;

import org.junit.Test;
public class RegexTest {

	/**
	 * @param args
	 */
	@Test
	public  void test() {
		String device = null;
		String tvSign = null;
		String matchString = "../qha/ce啊-11.JPEG          qinai阿斯顿";
		Pattern pattern1 = Pattern.compile("/(\\w|[\u4E00-\u9FA5])+(-|\\.)");
		Matcher matcher1 = pattern1.matcher(matchString);
		if (matcher1.find()){
		device = matcher1.group();
		device = device.substring(1);
		device = device.substring(0,device.length()-1);
		device.trim();
		}
		
		Pattern pattern2 = Pattern.compile("\\s(\\w|[\u4E00-\u9FA5])+$");
		Matcher matcher2 = pattern2.matcher(matchString);
		if (matcher2.find()){
		tvSign = matcher2.group();
		tvSign.trim();
		System.out.println("设备名："+device+"     "+"电视台："+tvSign);
		}
		

	}

}
