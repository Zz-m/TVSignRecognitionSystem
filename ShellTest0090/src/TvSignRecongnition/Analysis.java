package TvSignRecongnition;
import java.util.regex.*;

//../qinghai/qinghai-11.JPEG          qinghai
public class Analysis {
	/**
	 * 从输出结果提取设备名，以及匹配结果。
	 * @param line
	 * @return
	 */
	public static String[] analyse(String line) {
		
		String device = null;
		String tvSign = null;
		
		line = line.trim();
		Pattern pattern1 = Pattern.compile("/(\\w|[\u4E00-\u9FA5])+(-|\\.)");
		Matcher matcher1 = pattern1.matcher(line);
		if (matcher1.find()){
		device = matcher1.group();
		device = device.substring(1);
		device = device.substring(0,device.length()-1);
		device.trim();
		}
		
		Pattern pattern2 = Pattern.compile("\\s(\\w|[\u4E00-\u9FA5])+$");
		Matcher matcher2 = pattern2.matcher(line);
		if (matcher2.find()){
		tvSign = matcher2.group();
		tvSign.trim();
		}
		
		
		String[] result = {device,tvSign};
		return result;
	}

}
