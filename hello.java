public class hello{
	static {
		System.loadLibrary("hello");

	}

	private native void sayHello();

	public static void main( String[] args)
	{
		System.out.println("HELLO I AM JAVA");


		new hello().sayHello();

	}
}


