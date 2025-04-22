import React, { useState } from 'react';
import { Link } from 'react-router-dom';
import topStars from '../assets/images/topstars.png';
import bottomAlien from '../assets/images/aliencut.png';
import cowufo from '../assets/images/cowufo.png';
import universe from '../assets/images/universe.png';
import alien from '../assets/images/alienfullbody.png';
import starscut from '../assets/images/starscut.png';


export default function PredictionsPage() {
  const [year, setYear] = useState("2025");
  const [topCities, setTopCities] = useState("");
  const [bestTimes, setBestTimes] = useState("");
  const [topCityTimes, setTopCityTimes] = useState("");
  const [isRotating, setIsRotating] = useState(false);

  const handleYearChange = (e) => {
    const selectedYear = e.target.value;
    setYear(selectedYear);
    setIsRotating(true);

    Promise.all([
      fetch(`http://localhost:8080/top-cities?year=${selectedYear}`).then((res) => res.text()),
      fetch(`http://localhost:8080/top-times?year=${selectedYear}`).then((res) => res.text()),
      fetch(`http://localhost:8080/top-city-times?year=${selectedYear}`).then((res) => res.text())
    ])
      .then(([cities, times, cityTimes]) => {
        setTopCities(cities);
        setBestTimes(times);
        setTopCityTimes(cityTimes);
        setIsRotating(false);
      })
      .catch((err) => {
        console.error(err);
        setIsRotating(false);
      });
  };

  return (
    <div className="min-h-screen bg-[#F8F3E7] p-8">
      {/* Header */}
      <div className="flex justify-center relative">
        <h1 className="text-7xl font-bold font-grover text-primaryBlue">
          UFO Predictions
        </h1>
        <img
          src={universe}
          alt="universe"
          className={`absolute origin-center right-[40px] top-0 ${isRotating ? "animate-spin" : ""}`}
          style={{ width: '250px' }}
        />
      </div>

      {/* Dropdown */}
      <div className="-mt-14 pl-0 pr-0 flex items-center">
        <img src={alien} alt="alien" className="w-36 mr-4" />
        <p className="font-grover text-black text-left text-5xl mr-4">Select year</p>
        <select
          onChange={handleYearChange}
          value={year}
          className="text-3xl p-2 bg-[#8EB071] rounded border border-gray-500"
        >
          {Array.from({ length: 2014 - 1942 + 1 }, (_, i) => 2014 - i).map((y) => (
            <option key={y} value={y}>
              {y}
            </option>
          ))}
        </select>
      </div>



      <div className="mt-10 flex justify-center items-start gap-12 relative text-black font-grover">
        {/* Top 10 Locations */}
        <div className="bg-[#d9e7c4] border border-gray-600 rounded-2xl shadow-lg p-6 w-[300px] min-h-[380px] text-left">
          <h2 className="text-2xl font-bold text-center mb-4">Top 10 Locations</h2>
          <div className="whitespace-pre-line text-lg font-handlee leading-relaxed">
            {topCities || "Waiting for data..."}
          </div>
        </div>

        {/* ✨ */}
        <img
          src={starscut}
          alt="decorative stars"
          className="w-20 h-auto mt-14"
        />

        {/* Best Times */}
        <div className="bg-[#d9e7c4] border border-gray-600 rounded-2xl shadow-lg p-6 w-[300px] min-h-[380px] text-left">
          <h2 className="text-2xl font-bold text-center mb-4">Best Times</h2>
          <div className="whitespace-pre-line text-lg font-handlee leading-relaxed">
            {bestTimes || "Waiting for data..."}
          </div>
        </div>

        {/* ✨  */}
        <img
          src={starscut}
          alt="flipped decorative stars"
          className="w-20 h-auto mt-14 transform scale-x-[-1]"
        />

        {/* Best Times & Location */}
        <div className="bg-[#d9e7c4] border border-gray-600 rounded-2xl shadow-lg p-6 w-[300px] min-h-[380px] text-left">
          <h2 className="text-2xl font-bold text-center mb-4">Best Times & Location</h2>
          <div className="whitespace-pre-line text-lg font-handlee leading-relaxed">
            {topCityTimes || "Waiting for data..."}
          </div>
        </div>
      </div>




    </div>
  );
}
