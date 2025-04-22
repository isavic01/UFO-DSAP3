import { useEffect, useState } from "react";

export default function BestTimesAndLocations() {
  const [output, setOutput] = useState("");

  useEffect(() => {
    fetch("http://localhost:8080/top-city-times")
      .then((res) => res.text())
      .then(setOutput)
      .catch(console.error);
  }, []);

  return (
    <div className="p-4">
      <h2 className="text-2xl font-bold mb-2">Top Locations at Best Times</h2>
      <pre className="bg-gray-100 p-4 rounded">{output}</pre>
    </div>
  );
}
