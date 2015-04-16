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
		
		public void Print()
		{
			System.out.print("Total time elapsed in millisec is = ");
	        System.out.println(deltatime);
		}
		
		public long GetDeltaTime()
		{
			return deltatime;
		}
}
