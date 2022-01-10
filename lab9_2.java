public class lab9_2
{
	public static int count = 0;
	public static void main(String argv[])
	{
		int iter = 25000000;
		TH h1 = new TH(iter);
		Thread t1 = new Thread(h1);
		Thread t2 = new Thread(h1);
		Thread t3 = new Thread(h1);
		Thread t4 = new Thread(h1);
		t1.start();
		t2.start();
                t3.start();
                t4.start();
		try{	
			t1.join();
	                t2.join();
        	        t3.join();
                	t4.join();

		}
		catch(InterruptedException ie)
		{
			System.err.println(ie);
		}
		System.out.println("the count value is : "+count);
	}
}
class TH implements Runnable
{
	int iter = 0; 
	public TH(int num)
	{
		iter = num;
	}
	public void run()
	{
		int i=0;
		for(i=0;i<iter;i++)
		{
			lab9_2.count++;
		}
		System.out.println("Thread ID is "+Thread.currentThread().getName()+" Completed."+"count = "+lab9_2.count);
	}
}
