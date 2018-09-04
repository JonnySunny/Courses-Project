package planetwars.strategies;

import planetwars.publicapi.*;

import java.util.*;
/*

    Author: Don Le          lexxx675
            Zhongyi Sun     sunx0725


 */
public class iStrategy implements IStrategy {
    //Last Updated: 12-5
    //Method returns a projected population after some number of turns
    public ArrayList<Long> getProjectedPopulation(IVisiblePlanet planet, int numTurns) {
        int turnsPassed = 0;
        long size = planet.getSize();
        double penalty = 0.1;
        double growthRate = 1 + planet.getHabitability()/100.0;
        long projPop = planet.getPopulation();
        Long ownerID; //{-1,0,1} for opponent, neutral, and allied
        Owner owner = planet.getOwner();
        ArrayList<Long> result = new ArrayList<>(); //index 0 will be {-1,0,1} for opponent, neutral, and allied, and index 1 will be the population
        List<IShuttle> shuttleList = planet.getIncomingShuttles();

        //Population growth occurs first, then ally shuttles land, and then enemy shuttles land
        while (turnsPassed < numTurns) {
            turnsPassed += 1;
            //First handle population growth on the planet
            if (Math.abs(projPop) < size) {
                projPop = (long)(projPop * growthRate);
            }
            else if (Math.abs(projPop) >= size) {
                projPop = (long)(projPop - (projPop - size)*penalty);
            }
            long totalAttacking = 0;
            long otherAttacking = 0;
            //Now account for the incoming shuttles
            for (IShuttle shuttle : shuttleList) {
                //If planet is neutral, calculate number of allies and enemies coming on shuttles
                if (owner == Owner.NEUTRAL) {
                    if (shuttle.getOwner() == Owner.SELF) {
                        totalAttacking += shuttle.getNumberPeople();
                    }
                    else if (shuttle.getOwner() == Owner.OPPONENT) {
                        otherAttacking += shuttle.getNumberPeople();
                    }
                }
                //If planet is ally/enemy owned, then add the owner's shuttles first and sum the opposing shuttles
                else {
                    if (shuttle.getOwner() == owner && shuttle.getTurnsToArrival() == turnsPassed) {
                        projPop += shuttle.getNumberPeople();
                    } else if (shuttle.getOwner() != owner && shuttle.getTurnsToArrival() == turnsPassed) {
                        totalAttacking += shuttle.getNumberPeople();
                    }
                }
            }
            //Handle case that planet is neutral and shuttles are incoming
            if (owner == Owner.NEUTRAL) {
                if (totalAttacking > otherAttacking) {
                    owner = Owner.SELF;
                    projPop = totalAttacking - otherAttacking;
                }
                else if (otherAttacking > totalAttacking) {
                    owner = Owner.OPPONENT;
                    projPop = otherAttacking - totalAttacking;
                }
            }
            //Below handle the case that we are not neutral. This accounts for the defense bonus
            else if (1.1*projPop > totalAttacking) {
                projPop = (long)(Math.min(projPop, 1.1*projPop - totalAttacking));
            }
            else if (1.1*projPop < totalAttacking) {
                projPop = (long)(totalAttacking - 1.1*projPop);
                if (owner == Owner.SELF) {owner = Owner.OPPONENT;}
                else {owner = Owner.SELF;}
            }
            else if ((long)(1.1*projPop) == totalAttacking) {
                projPop = 0;
                owner = Owner.NEUTRAL;
            }
        }
        //assign number depending on who owns the planet
        if (owner == Owner.OPPONENT) {ownerID = (long)(-1);}
        else if (owner == Owner.NEUTRAL) {ownerID = (long)(0);}
        else {ownerID = (long)(1);}
        result.add(ownerID);
        result.add(projPop);

        return result;
    }

    //Method to get planets connected the passed planet, sorted into ones the calling player owns and the others (neutral/enemy)
    //planet is the current planet you want connected planets for. myVisiblePlanets should be a HashMap of the planets owned, otherVisiblePlanets are the neutral/enemy planets
    public ArrayList<HashMap<Integer, Integer>> getConnectedPlanets(IVisiblePlanet planet, HashMap<Integer, IVisiblePlanet> myVisiblePlanets, HashMap<Integer, IVisiblePlanet> otherVisiblePlanets) {
        HashMap<Integer, Integer> myConnectedPlanets = new HashMap<>(); //Map with planet IDs as keys and the distance to that planet
        HashMap<Integer, Integer> otherConnectedPlanets = new HashMap<>();
        ArrayList<HashMap<Integer, Integer>> result = new ArrayList<>();
        Set<IEdge> edges = planet.getEdges();

        //loop through edges to find all the planets connected to the current plant as well as their distance, sorted into different HashMaps
        for (IEdge edge : edges) {
            if (myVisiblePlanets.containsKey(edge.getDestinationPlanetId())) {
                myConnectedPlanets.put(edge.getDestinationPlanetId(), edge.getLength());
            }
            else if (otherVisiblePlanets.containsKey(edge.getDestinationPlanetId())) {
                otherConnectedPlanets.put(edge.getDestinationPlanetId(), edge.getLength());
            }
        }
        result.add(myConnectedPlanets);
        result.add(otherConnectedPlanets);
        return result;
    }

    public HashMap<String, ArrayList<Integer>> getConnectedIDs(IVisiblePlanet planet, HashMap<Integer, IVisiblePlanet> myVisiblePlanets, HashMap<Integer, IVisiblePlanet> otherVisiblePlanets) {
        Set<IEdge> edges = planet.getEdges();
        ArrayList<Integer> connIDs = new ArrayList<>();
        ArrayList<Integer> otherConnIDs = new ArrayList<>();
        HashMap<String, ArrayList<Integer>> result = new HashMap<>();

        //loop through edges to find all the planets connected to the current plant as well as their distance, sorted into different ArrayLists
        for (IEdge edge : edges) {
            if (myVisiblePlanets.containsKey(edge.getDestinationPlanetId())) {
                connIDs.add(edge.getDestinationPlanetId());
            }
            else if (otherVisiblePlanets.containsKey(edge.getDestinationPlanetId())) {
                otherConnIDs.add(edge.getDestinationPlanetId());
            }
        }
        result.put("myConnIDs", connIDs);
        result.put("otherConnIDs", otherConnIDs);
        return result;
    }

    //Method to get all populations of planets given in the List IDs. Useful for keeping track of temp populations when we're sending shuttles out.
    public HashMap<Integer, Long> getAllPopulations(HashMap<Integer, IVisiblePlanet> planets, List<Integer> IDs) {
        HashMap<Integer, Long> result = new HashMap<>();
        for (Integer i : IDs) {
            result.put(i, planets.get(i).getPopulation()); //Store ID as key and planet population as value
        }
        return result;
    }

    @Override
    public void takeTurn(List<IPlanet> planets, IPlanetOperations planetOperations, Queue<IEvent> eventsToExecute) {

        HashMap<Integer, IVisiblePlanet> myVisiblePlanets = new HashMap<>(); //visible planets owned
        HashMap<Integer, IVisiblePlanet> otherVisiblePlanets = new HashMap<>(); //visible planets that are neutral/enemy owned
        ArrayList<Integer> myIds = new ArrayList<>(); //Store IDs of myVisiblePlanets to iterate later
        ArrayList<Integer> otherIds = new ArrayList<>(); //Store IDs of otherVisiblePlanets to iterate later

        //Go through list of planets and store all visible planets as owned versus neutral/enemy owned
        for (IPlanet planet : planets) {
            if (planet instanceof IVisiblePlanet && ((IVisiblePlanet) planet).getOwner() == Owner.SELF) {
                myVisiblePlanets.put(planet.getId(), (IVisiblePlanet) planet);
                myIds.add(planet.getId());
            } else if (planet instanceof IVisiblePlanet) {
                otherVisiblePlanets.put(planet.getId(), (IVisiblePlanet) planet);
                otherIds.add(planet.getId());
            }
        }

        HashMap<Integer, Long> myConnPlanetsCurrPop = getAllPopulations(myVisiblePlanets, myIds); //use to keep track of populations of our planets as we send shuttles

        //Loop through planets that are not owned (neutral or enemy)
        for (Integer i : otherIds) {

            IVisiblePlanet getEdgesFrom = otherVisiblePlanets.get(i); //Current planet we are observing

            HashMap<Integer, Integer> myConnectedPlanets; //store IDs as keys and the distance to this planet
            ArrayList<Integer> connIds;                    //Store IDs to iterate later
            HashMap<Integer, Integer> otherConnectedPlanets;
            ArrayList<Integer> otherConnIds;

            //Store the planets connected to the current one using the getConnectedPlanets() method
            ArrayList<HashMap<Integer, Integer>> distanceInfo = getConnectedPlanets(getEdgesFrom, myVisiblePlanets, otherVisiblePlanets);
            //Store the planet IDs of those connected planets
            HashMap<String, ArrayList<Integer>> IDInfo = getConnectedIDs(getEdgesFrom, myVisiblePlanets, otherVisiblePlanets);

            myConnectedPlanets = distanceInfo.get(0); //Get a HashMap of allied connected planets with IDs as keys and distances as values
            // otherConnectedPlanets = distanceInfo.get(1); //Get a hashmap for neutral/enemy connected planets
            connIds = IDInfo.get("myConnIDs"); //List of owned, connected planet IDs
            //otherConnIds = IDInfo.get("otherConnIDs"); //List of neutral,enemy connected planet IDs

            //If we find a neutral planet, we should send people to it to maximize overall growth
            if (getEdgesFrom.getOwner() == Owner.NEUTRAL) {
                //Loop through connected planets
                for (Integer j : connIds) {
                    IVisiblePlanet source = myVisiblePlanets.get(j);
//                    if (myConnPlanetsCurrPop.get(j) < 4) {continue;}
                    long numToSend =(long)((0.8)*myConnPlanetsCurrPop.get(j)); //default number of people to send

                    //loop while the number of people to send is too large
                    while (numToSend > getEdgesFrom.getSize()) {
                        numToSend = (long)(numToSend * (0.5));
                    }

                    eventsToExecute.offer(planetOperations.transferPeople(source, getEdgesFrom, numToSend));
                    myConnPlanetsCurrPop.put(j, myConnPlanetsCurrPop.get(j) - numToSend); //subtract the people sent from the population

                }
            }

            //if we find an opponent planet, check if we can conquer it
            else if (getEdgesFrom.getOwner() == Owner.OPPONENT) {
                //Keep two ArrayLists to check if we ever send people from one of our planets
                ArrayList<Integer> sentFrom = new ArrayList<>();
                ArrayList<Integer> notSentFrom = new ArrayList<>();
                //Loop through the connected planets
                for (Integer k : connIds) {
                    IVisiblePlanet source = myVisiblePlanets.get(k); //get planet objct
                    ArrayList<Long> projPop = getProjectedPopulation(getEdgesFrom, myConnectedPlanets.get(k)); //get the projected population

                    if (myConnPlanetsCurrPop.get(k) < 5) {continue; } //don't send people if the population is too low
                    //if planet is projected to be neutral or enemy owned and we have enough people, send shuttles
                    if ((projPop.get(0) == -1 | projPop.get(0) == 0) && (myConnPlanetsCurrPop.get(k) > 1.1 * projPop.get(1))) {

                        long numToSend = (long) ((0.5) * source.getPopulation());
                        while (numToSend < 1.1 * projPop.get(1) && numToSend < myConnPlanetsCurrPop.get(k)) {//loop while the number of people to send is too small and less than the population
                            numToSend = (long) (numToSend * 1.5);
                        }
                        eventsToExecute.offer(planetOperations.transferPeople(source, getEdgesFrom, numToSend));
                        myConnPlanetsCurrPop.put(k, myConnPlanetsCurrPop.get(k) - numToSend); //subtract the people send from the population
                        sentFrom.add(k); //add to ArrayList to show  that we've sent people to the current planet from this planet
                    } else {
                        notSentFrom.add(k);
                    }
                }
                //if we could not sent enough people from one planet, check if we can use sent shuttles from multiple planets
                if (sentFrom.isEmpty() && notSentFrom.size() > 1) {
                    Long maxToSend = (long)0;
                    Integer avgDist = 0;

                    for (Integer h : notSentFrom) {
                        maxToSend += myConnPlanetsCurrPop.get(h);
                        avgDist += myConnectedPlanets.get(h);
                    }
                    avgDist = avgDist/notSentFrom.size();
                    ArrayList<Long> projPop = getProjectedPopulation(getEdgesFrom, avgDist); //use the average distance of allied planets to see if we have enough people from multiple planets

                    if (0.7*maxToSend > 1.1*projPop.get(1)) {
                        for (Integer g : notSentFrom) {
                            Long numToSend = (long)(0.7*myConnPlanetsCurrPop.get(g));
                            eventsToExecute.offer(planetOperations.transferPeople(myVisiblePlanets.get(g), getEdgesFrom, numToSend)); //send people from each allied planet that is connected
                            myConnPlanetsCurrPop.put(g, myConnPlanetsCurrPop.get(g) - numToSend );
                        }
                    }
                }
            }

        }

        //Loop through our own planets now
        for (Integer j : myIds) {

            IVisiblePlanet getEdgesFrom = myVisiblePlanets.get(j); //Current planet we are observing
            //Store the planets that are connected to the current planet we are looking at
            PriorityQueue<Long> myConnectedLostPriorityQueue = new PriorityQueue<>();
            PriorityQueue<Long> myConnectedKeptPriorityQueue = new PriorityQueue<>();
            HashMap<Integer, Integer> myConnectedPlanets;
            List<Integer> connIds;
            HashMap<Integer, Integer> otherConnectedPlanets;
            //List<Integer> otherConnIds;
            HashMap<Long, Integer> queuedIds = new HashMap<>();

            ArrayList<HashMap<Integer, Integer>> distanceInfo = getConnectedPlanets(getEdgesFrom, myVisiblePlanets, otherVisiblePlanets);
            HashMap<String, ArrayList<Integer>> IDInfo = getConnectedIDs(getEdgesFrom, myVisiblePlanets, otherVisiblePlanets);

            myConnectedPlanets = distanceInfo.get(0); //Get a HashMap of allied connected planets with IDs as keys and distances as values
            otherConnectedPlanets = distanceInfo.get(1); //Get a HashMap for neutral/enemy connected planets
            connIds = IDInfo.get("myConnIDs"); //List of owned, connected planet IDs
            //otherConnIds = IDInfo.get("otherConnIDs"); //List of neutral,enemy connected planet IDs

            //Loop through surrounding, allied planets to check if there are no neutral/enemy planets connected
            //If a planet is 'safe' i.e. it is not surrounded by any enemies or neutral planets, we should sent reinforcements to other planets
            if (otherConnectedPlanets.isEmpty()) {
                for (Integer i : connIds) {
                    ArrayList<Long> projPop = getProjectedPopulation(myVisiblePlanets.get(i), myConnectedPlanets.get(i));
                    //If we're projected to lose a planet, add it to the appropriate queue
                    if (projPop.get(0) == 0 | projPop.get(0) == -1) {
                        myConnectedLostPriorityQueue.add(projPop.get(1));
                        queuedIds.put(projPop.get(1), i);
                    }
                    //If we're not projected to lose a planet, add it to the other queue
                    else if (projPop.get(0) == 1) {
                        myConnectedKeptPriorityQueue.add(projPop.get(i));
                        queuedIds.put(projPop.get(1), i);
                    }
                }

                //if we're not projected to lose any nearby allied planets, send reinforcements to the planet with the lowest projected population
                if (myConnectedLostPriorityQueue.isEmpty()) {
                    Long priorityId = myConnectedKeptPriorityQueue.peek(); //check the lowest projected population and use it as an ID
                    Integer priorityPlanetId = queuedIds.get(priorityId); //get the actual planet ID
                    IVisiblePlanet sendTo = myVisiblePlanets.get(priorityPlanetId); //get the planet to send reinforcements to
                    ArrayList<Long> projPop = getProjectedPopulation(sendTo, myConnectedPlanets.get(priorityPlanetId)); //projected population

                    if (myConnPlanetsCurrPop.get(j) > 2) {//don't send people if our population is too small
                        Long numToSend = (long)(0.9*myConnPlanetsCurrPop.get(j));
                        //Loop until the number is small enough
                        while (numToSend > sendTo.getSize()) {
                            numToSend = (long)(numToSend * 0.9);
                        }
                        eventsToExecute.offer(planetOperations.transferPeople(getEdgesFrom, sendTo, numToSend));
                        myConnPlanetsCurrPop.put(priorityPlanetId, myConnPlanetsCurrPop.get(priorityPlanetId) - numToSend); //keep track of current population
                    }
                }
                //if we're projected to lose a planet we should send reinforcements to the one with the lowest projected population as it will be the easiest to recapture
                else {
                    Long priorityId = myConnectedLostPriorityQueue.peek();
                    Integer priorityPlanetId = queuedIds.get(priorityId);
                    IVisiblePlanet sendTo = myVisiblePlanets.get(priorityPlanetId);
                    ArrayList<Long> projPop = getProjectedPopulation(sendTo, myConnectedPlanets.get(priorityPlanetId));

                    if (myConnPlanetsCurrPop.get(j) > 3) {//don't send people if the population is too small
                        Long numToSend =  (long)(0.9*myConnPlanetsCurrPop.get(priorityPlanetId));
                        //Loop while the number of people to send is too small
                        while (numToSend > sendTo.getSize()) {
                            numToSend = (long)(numToSend * 0.9);
                        }
                        eventsToExecute.offer(planetOperations.transferPeople(getEdgesFrom, sendTo, numToSend));
                        myConnPlanetsCurrPop.put(priorityPlanetId, myConnPlanetsCurrPop.get(priorityPlanetId) - numToSend);
                    }

                }
            }
        }
    }

    @Override
    public String getName() {
        return "Don/Zhongyi";
    }

    @Override
    public boolean compete() {
        return false;
    }
}

