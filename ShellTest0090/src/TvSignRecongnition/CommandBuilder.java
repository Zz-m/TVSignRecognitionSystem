package TvSignRecongnition;

public class CommandBuilder {
	/**
	 * ����shell����
	 * @param args
	 * @return
	 * ./MATCHDIR  ./trainDataDir/  ./indexFile  ./featureDataDir/  ./anhui 
	 */
	public static String buildCommand (String[] args) {
		if(args.length != 1){
			System.out.println("�������ͼ��·��   ��./workspace/test/beijing/");
            return "fail";
		}
		String commands = "./MATCHDIR"+" "+"./trainDataDir/"+" "+"./indexFile"+" "+"./featureDataDir/"+" "+args[0];
		
		return commands;
		
	}
}
