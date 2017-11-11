package com.flin.code;

import com.flin.code.bean.Journey;
import com.flin.code.bean.PathSegment;
import org.junit.Before;
import org.junit.Test;

import java.util.ArrayList;

import static org.junit.Assert.assertEquals;
import static org.mockito.Mockito.doAnswer;
import static org.mockito.Mockito.spy;

public class ResolverTest {

    private Resolver resolver;

    @Before
    public void setUp() throws Exception {
        resolver = spy(Resolver.class);
        doAnswer((i) -> new Journey(20, 60)).when(resolver).readJourney();
        doAnswer((i) -> new ArrayList<PathSegment>() {{
            add(new PathSegment(0, 30, 10));
            add(new PathSegment(30, 40, 20));
            add(new PathSegment(40, 80, 20));
            add(new PathSegment(80, 100, 5));
        }}).when(resolver).readSegments();
    }

    @Test
    public void resolve() throws Exception {
        assertEquals(2.50, resolver.resolve(), 0.01);
    }

}