package TvSignRecongnition;

public class CommandBuilder {
	/**
	 * 构建shell命令
	 * @param args
	 * @return
	 * ./MATCHDIR  ./trainDataDir/  ./indexFile  ./featureDataDir/  ./anhui 
	 */
	public static String buildCommand (String[] args) {
		if(args.length != 1){
			System.out.println("输入待测图标路径   如./workspace/test/beijing/");
            return "fail";
		}
		String commands = "./MATCHDIR"+" "+"./trainDataDir/"+" "+"./indexFile"+" "+"./featureDataDir/"+" "+args[0];
		
		return commands;
		
	}
}
