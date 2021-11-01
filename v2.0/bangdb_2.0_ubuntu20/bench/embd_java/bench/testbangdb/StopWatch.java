package testbangdb;

public class StopWatch {
	
		long stime;
		long deltatime;
		public StopWatch()
		{
			stime = 0;
			deltatime = 0;
		}
		public void Start()
		{
			stime = System.currentTimeMillis();
		}
		public void Stop()
		{
			deltatime = System.currentTimeMillis() - stime;
		}
		
		public void Print(int N)
		{
			//System.out.print("Total time elapsed in millisec is = ");
			long tp = (deltatime > 0) ? (N*1000)/deltatime : N;
	        	System.out.println(deltatime + " millisec, throughput = " + tp +" ops/sec");
		}
		
		public long GetDeltaTime()
		{
			return deltatime;
		}
}
