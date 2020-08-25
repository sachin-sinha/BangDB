package testbangdb;

public class TestMain {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		 if(args.length == 0)
		 {
			 System.out.println("To run the test use following command;");
			 System.out.println("exapp <number_items> <num_threads>");
			 System.out.println("Running Simple Sanity Test");
			 TestCases.testsanity();
			 return;
		 }
		 else if(args.length == 1)
		 {
			 int N = Integer.parseInt(args[0]);
			 int nthrds = Runtime.getRuntime().availableProcessors();
			 System.out.printf("Running get and put perf test for num of items = %d with %d threads\n", N, nthrds);
			 TestCases.testputget(N, nthrds);
        	 	return;
		 }
		 else if(args.length == 2)
         	 {
			 int N = Integer.parseInt(args[0]);
			 int nthrds = Integer.parseInt(args[1]);
			 System.out.printf("Running get and put perf test for num of items = %d with %d threads\n", N, nthrds);
			 TestCases.testputget(N, nthrds);
        	 	return;
         	 }

     		 return;
	}
}
