#pragma once

/*
Long duration lambda wrapper, which are generally not supported by the taskgraph system. New thread per lambda and they will auto-delete upon
completion.
*/
class FSIOLambdaRunnableUEtopia : public FRunnable
{
private:
	/** Thread to run the worker FRunnable on */
	FRunnableThread* Thread;
	uint64 Number;

	//Lambda function pointer
	TFunction< void()> FunctionPointer;

	/** Use this thread-safe boolean to allow early exits for your threads */
	FThreadSafeBool Finished;

	//static TArray<FLambdaRunnable*> Runnables;
	static uint64 ThreadNumber;

public:
	//~~~ Thread Core Functions ~~~

	//Constructor / Destructor
	FSIOLambdaRunnableUEtopia(TFunction< void()> InFunction);
	virtual ~FSIOLambdaRunnableUEtopia();

	// Begin FRunnable interface.
	virtual bool Init();
	virtual uint32 Run();
	virtual void Stop();
	void Kill();
	virtual void Exit() override;
	// End FRunnable interface

	/** Makes sure this thread has stopped properly */
	void EnsureCompletion();
	

	/*
	Runs the passed lambda on the background thread, new thread per call
	*/
	static FSIOLambdaRunnableUEtopia* RunLambdaOnBackGroundThread(TFunction< void()> InFunction);


	/*
	Runs a short lambda on the game thread via task graph system
	*/
	static FGraphEventRef RunShortLambdaOnGameThread(TFunction< void()> InFunction);

	static void ShutdownThreads();
};