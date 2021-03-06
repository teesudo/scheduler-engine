package com.sos.scheduler.engine.test.util;

import com.google.common.io.Resources;
import com.sos.scheduler.engine.kernel.scheduler.SchedulerConstants;
import org.joda.time.DateTime;
import org.joda.time.format.DateTimeFormatter;
import org.joda.time.format.ISODateTimeFormat;
import org.junit.Test;

import java.io.IOException;
import java.net.URL;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertTrue;

public final class CommandBuilderTest {

    private static final String expectedBuildCommandAddOrder = "com/sos/scheduler/engine/test/util/CommandBuilder-expectedAddOrder.txt";
    private static final String expectedBuildCommandAddOrderWithParams = "com/sos/scheduler/engine/test/util/CommandBuilder-expectedAddOrderWithParams.txt";
    private static final String expectedBuildCommandAddOrderWithParams2 = "com/sos/scheduler/engine/test/util/CommandBuilder-expectedAddOrderWithParams2.txt";
    private static final String expectedBuildCommandStartJobImmidiately = "com/sos/scheduler/engine/test/util/CommandBuilder-expectedStartJobImmediately.txt";

    private final CommandBuilder util = new CommandBuilder();

    @Test
    public void addOrderTest() throws IOException {
        String command = util.addOrder("myJobchain").getCommand();
        URL expectedURL = Resources.getResource(expectedBuildCommandAddOrder);
        String expectedCommand = Resources.toString(expectedURL, SchedulerConstants.defaultEncoding);
        assertEquals(expectedCommand,command);
    }

    @Test
    public void addOrderWithParamsTest() throws IOException {
        String command = util.addOrder("myJobchain").addParam("myParam1", "value1").getCommand();
        URL expectedURL = Resources.getResource(expectedBuildCommandAddOrderWithParams);
        String expectedCommand = Resources.toString(expectedURL, SchedulerConstants.defaultEncoding);
        assertEquals(expectedCommand,command);
    }

    @Test
    public void addOrderWithParams2Test() throws IOException {
        util.addParam("myParam1", "value1");
        util.addParam("myParam2", "value2");
        String command = util.addOrder("myJobchain").getCommand();
        URL expectedURL = Resources.getResource(expectedBuildCommandAddOrderWithParams2);
        String expectedCommand = Resources.toString(expectedURL, SchedulerConstants.defaultEncoding);
        assertEquals(expectedCommand,command);
    }

    @Test
    public void showCalendarTest() {
        int duration = 60;
        String command = util.showCalendar(duration, What.orders).getCommand();
        DateTime begin = util.getLastBegin();
        DateTime end = util.getLastEnd();
        DateTimeFormatter fmt = ISODateTimeFormat.dateHourMinuteSecond();
        String expectedFile = "<show_calendar before='" + fmt.print(end) + "' from='" + fmt.print(begin) + "' limit='10' what='orders'></show_calendar>";
        assertTrue("expected value is '" + expectedFile + "'",expectedFile.equals(command));
    }

    @Test
    public void startJobImmidiatelyTest() throws IOException {
        util.addParam("myParam1", "value1");
        util.addParam("myParam2", "value2");
        String command = util.startJobImmediately("myJob").getCommand();
        URL expectedURL = Resources.getResource(expectedBuildCommandStartJobImmidiately);
        String expectedCommand = Resources.toString(expectedURL, SchedulerConstants.defaultEncoding);
        assertEquals(expectedCommand,command);
    }
}
